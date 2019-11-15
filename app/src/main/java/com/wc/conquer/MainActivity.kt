package com.wc.conquer

import android.Manifest
import android.content.pm.PackageManager
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.support.v4.app.ActivityCompat
import android.support.v4.content.ContextCompat
import com.wc.breakpad.BreakpadInit
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File


/**
 * Android NDK:https://github.com/android/ndk-samples
 */
class MainActivity : AppCompatActivity() {

    private val writeExternalStorageRequestCode: Int = 100
    private var externalReportPath: File? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // 申请访问sdcard权限
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) !=
                PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(
                    this,
                    arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE),
                    writeExternalStorageRequestCode)
        } else {
            initExternalReportPath()
        }

        // Example of a call to a native method
        sample_text.text = stringFromJNI()

        sample_text.setOnClickListener({
            initBreakPad()
            crash()
        })
    }

    private fun initExternalReportPath() {
        externalReportPath = File(Environment.getExternalStorageDirectory(), "crashDump")
        if (!externalReportPath!!.exists()) {
            externalReportPath!!.mkdirs()
        }
    }

    private fun initBreakPad() {
        if (externalReportPath == null) {
            externalReportPath = File(filesDir, "crashDump")
            if (!externalReportPath!!.exists()) {
                externalReportPath!!.mkdirs()
            }
        }
        BreakpadInit.initBreakpad(externalReportPath!!.absolutePath)
    }

    private external fun crash()

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    private external fun stringFromJNI(): String

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

    // 观看写法
    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        initExternalReportPath()
    }


}
