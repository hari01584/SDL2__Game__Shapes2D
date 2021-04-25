if (NOT EXISTS "F:/AndroidNative/android-project/app/.cxx/cmake/debug/x86_64/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"F:/AndroidNative/android-project/app/.cxx/cmake/debug/x86_64/install_manifest.txt\"")
endif(NOT EXISTS "F:/AndroidNative/android-project/app/.cxx/cmake/debug/x86_64/install_manifest.txt")

file(READ "F:/AndroidNative/android-project/app/.cxx/cmake/debug/x86_64/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND C:/Users/hari0/AppData/Local/Android/Sdk/cmake/3.10.2.4988404/bin/cmake.exe -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

