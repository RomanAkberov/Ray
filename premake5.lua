workspace "Ray"
    configurations {"Debug", "Release"}
    systemversion "latest"
    warnings "Extra"

project "Ray"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    files "source/**"

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"
        