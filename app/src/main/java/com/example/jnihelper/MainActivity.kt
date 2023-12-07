package com.example.jnihelper

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import com.example.jnihelper.databinding.ActivityMainBinding
import java.lang.reflect.InvocationTargetException
import java.lang.reflect.Method

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    fun getClassLoaderClasses(classLoader: ClassLoader) : Array<String> {
        val result = ArrayList<String>()
        try {
            val baseDexClassLoaderClass = classLoader.loadClass("dalvik.system.BaseDexClassLoader")!!
            val pathListField = baseDexClassLoaderClass.getDeclaredField("pathList")
            pathListField.isAccessible = true
            val pathListObj = pathListField[classLoader]
            val pathListClass = classLoader.loadClass("dalvik.system.DexPathList")!!
            val dexElementsField = pathListClass.getDeclaredField("dexElements")
            dexElementsField.isAccessible = true
            val dexElementArray = dexElementsField[pathListObj] as Array<*>
            //forName
            //loadClass
            val elementClass = classLoader.loadClass("dalvik.system.DexPathList\$Element")!!
            val dexFileField = elementClass.getDeclaredField("dexFile")
            dexFileField.isAccessible = true
            val dexFileClass = classLoader.loadClass("dalvik.system.DexFile")!!
            val mCookieField = dexFileClass.getDeclaredField("mCookie")
            mCookieField.isAccessible = true
            val methods = dexFileClass.declaredMethods
            var getClassNameListMethod: Method? = null
            for (i in methods) {
                if (i.name == "getClassNameList") {
                    getClassNameListMethod = i
                    getClassNameListMethod.isAccessible = true
                }
            }
//            Log.i("LOG", "ClassLoaderClasses from $classLoader")
            for (element in dexElementArray) {
                val dexFileObj = dexFileField[element]
                val mCookieObj = mCookieField[dexFileObj]
                val classList =
                    getClassNameListMethod!!.invoke(dexFileObj, mCookieObj) as Array<String>
//                Log.i("LOG", "$element")
                for (classname in classList) {
//                    Log.i("LOG", "--->$classname")
                    result.add(classname)
                }
            }
            //private Element[] dexElements;
        } catch (e: ClassNotFoundException) {
            e.printStackTrace()
        } catch (e: NoSuchFieldException) {
            e.printStackTrace()
        } catch (e: IllegalAccessException) {
            e.printStackTrace()
        } catch (e: InvocationTargetException) {
            e.printStackTrace()
        }
        return result.toArray(arrayOf(""))
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method

        binding.sampleText.text = stringFromJNI()
        val stringArray = getClassLoaderClasses(classLoader)
        for (i in reverseStringArray(stringArray)){
//            Log.e("LOG", i)
        }
    }

    /**
     * A native method that is implemented by the 'jnihelper' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun reverseStringArray(stringArray: Array<String>): Array<String>

    companion object {
        // Used to load the 'jnihelper' library on application startup.
        init {
            System.loadLibrary("jnihelper")
        }
    }
}