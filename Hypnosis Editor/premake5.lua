project "Hypnosis Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/" .. outputdir .. "/%{prj.name}/")
    objdir ("%{wks.location}/" .. outputdir .. "/%{prj.name}/Int")

    files
    {
        "Source/**.h",
        "Source/**.cpp",        
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    characterset("MBCS")

    includedirs
    {
        "Source",
        "%{wks.location}/Hypnosis/Source",
        "%{wks.location}/Hypnosis/Dependencies",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.assimp}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.parson}",
    }

    links
    {
        "Hypnosis",
    }

    

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
        }

    filter "configurations:Debug"
        -- defines here
        defines {"SPDLOG_COMPILED_LIB"}
        runtime "Debug"
        buildoptions "/MTd"
        symbols "On"

    filter "configurations:Release"
        -- defines here
        defines {"SPDLOG_COMPILED_LIB"}
        runtime "Release"
        buildoptions "/MT"
        optimize "On"
