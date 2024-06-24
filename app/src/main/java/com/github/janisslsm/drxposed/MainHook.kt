package com.github.janisslsm.DRXposed

import android.content.Context
import de.robv.android.xposed.*
import de.robv.android.xposed.XposedHelpers.findAndHookMethod
import de.robv.android.xposed.XposedHelpers.findAndHookConstructor
import de.robv.android.xposed.callbacks.XC_LoadPackage
import java.io.File


class MainHook : IXposedHookLoadPackage {
    private var drContext: Context? = null;

    /* 
        Add Original Game's package.name and some modded package.name
        Official Free and Premium
        Angel and DXV Mods
        and Lazy Clones made by MT Manager
    */
    
    private val allowedPackages = listOf(
        "com.gm_shaber.dayr",
        "com.gm_shaber.dayrpremium",
        "app.angelmod.dayr",
        "app.angelmod.dayr_dev",
        "com.diexievie.dayr",
        "com.diexievie.dayr_dev",
        "com.gm_shaber.days",
        "com.gm_shaber.dayrpremiun"
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

                // Help, idk what to find, hope it works
                findAndHookConstructor(
                    "com.naef.jnlua.LuaState", 
                    lpparam.classLoader, 
                    Long::class.javaPrimitiveType, // Use Long::class.javaPrimitiveType for primitive long type
                    object : XC_MethodHook() {
                        override fun afterHookedMethod(param: MethodHookParam?) {
                            val scriptsDirectory = File("${drContext!!.getExternalFilesDir(null)}/scripts")
                            if (!scriptsDirectory.exists()) 
                                scriptsDirectory.mkdirs();
                            scriptsDirectory.listFiles()?.let { runFiles(it) }
                       }
                })
                
                /*
                // Had this Commented out because this patch runs after the game fully initialized
                // If you wanted to patch important things such as Constants Value Ingame, 
                // you need to patch it before the game finish loading (loads a profile as in continuing game)
                // since this plugin is the last entry loaded after main.loading.loadProfile(profileID) fires
                
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
                */
                System.loadLibrary("DRXposed")

            } catch (e: Throwable) {
                XposedBridge.log(e)
            }
        }
    }

    external fun loadstring(code: String): Int
    external fun loadfile(path: String): Int
}
