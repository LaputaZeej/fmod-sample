package com.laputa.fmod

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.laputa.fmod.FmodHelper.Companion.MODE_DASHU
import com.laputa.fmod.FmodHelper.Companion.MODE_KONGLING
import com.laputa.fmod.FmodHelper.Companion.MODE_LOLI
import com.laputa.fmod.FmodHelper.Companion.MODE_NORMAL
import com.laputa.fmod.databinding.ActivityMainBinding
import org.fmod.FMOD

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()
        FMOD.init(this)
        binding.initViews()
    }

    private fun ActivityMainBinding.initViews() {
        btn01.setOnClickListener {
            nativeChangeVoice(MODE_NORMAL)

        }
        btn02.setOnClickListener {
            nativeChangeVoice(MODE_LOLI)

        }
        btn03.setOnClickListener {
            nativeChangeVoice(MODE_DASHU)

        }
        btn04.setOnClickListener {
            nativeChangeVoice(MODE_KONGLING)

        }

        btn05.setOnClickListener {
            nativeChangeVoice(-1)

        }
    }

    private external fun nativeChangeVoice(mode: Int, path: String = PATH)

    override fun onDestroy() {
        super.onDestroy()
        FMOD.close()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }

        private const val PATH = "file:///android_asset/a.wav"

    }
}