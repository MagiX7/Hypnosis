project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

    targetdir ("%{wks.location}/" .. outputdir .. "/%{prj.name}/")
    objdir ("%{wks.location}/" .. outputdir .. "/%{prj.name}/Int")

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Hypnosis/Dependencies/spdlog/include",
		"%{wks.location}/Hypnosis/Source",
		"%{wks.location}/Hypnosis/Dependencies",
		"%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
	}

	links
	{
		"Hypnosis"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		buildoptions "/MTd"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		buildoptions "/MT"
		optimize "on"