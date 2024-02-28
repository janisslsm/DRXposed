package com.github.janisslsm.DRXposed

import android.content.Context
import de.robv.android.xposed.*
import de.robv.android.xposed.XposedHelpers.findAndHookMethod
import de.robv.android.xposed.callbacks.XC_LoadPackage
import java.io.File


class MainHook : IXposedHookLoadPackage {
    private var drContext: Context? = null;

    // Add Original Game's package.name and some modded package.name
    private val allowedPackages = listOf(
        "com.gm_shaber.dayr",
        "com.gm_shaber.dayrpremium", 
        "app.angel_mod.dayr",
        "app.angelmod.dayr",
        "app.dxv_mod.dayr",
        "app.dxvmod.dayr"
    )

    fun runFiles(files: Array<File>) {
        for (file in files) {
            if (file.isDirectory) {
                file.listFiles()?.let { runFiles(it) } // Calls same method again.
            } else {
                if(file.extension == "lua")
                    loadfile(file.absolutePath)
            }
        }
    }

    override fun handleLoadPackage(lpparam: XC_LoadPackage.LoadPackageParam) {
        if (allowedPackages.contains(lpparam.packageName)) {
            try {
                findAndHookMethod("android.content.ContextWrapper", lpparam.classLoader, "getApplicationContext", object : XC_MethodHook() {
                    @Throws(Throwable::class)
                    override fun afterHookedMethod(param: MethodHookParam) {
                        val applicationContext = param.result as Context
                        if(drContext == null) {
                            drContext = applicationContext;
                            val scriptsDirectory = File("${drContext!!.getExternalFilesDir(null)}/scripts");
                            if(!scriptsDirectory.exists())
                                scriptsDirectory.mkdirs();
                        }
                    }
                })
                findAndHookMethod("plugin.notifications.v2.LuaLoader", lpparam.classLoader, "invoke",
                    "com.naef.jnlua.LuaState",
                    object : XC_MethodHook() {
                        override fun afterHookedMethod(param: MethodHookParam?) {
                            val scriptsDirectory = File("${drContext!!.getExternalFilesDir(null)}/scripts");
                            if(!scriptsDirectory.exists())
                                scriptsDirectory.mkdirs();
                            scriptsDirectory.listFiles()?.let { runFiles(it) }
                        }
                    })
                System.loadLibrary("DRXposed")

            } catch (e: Throwable) {
                XposedBridge.log(e)
            }
        }
    }

    external fun loadstring(code: String): Int
    external fun loadfile(path: String): Int
}
