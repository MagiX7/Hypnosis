include "Dependencies.lua"

workspace "Hypnosis"
	architecture "x86"
	startproject "Hypnosis Editor"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "Build/%{cfg.buildcfg}"

group "Dependencies"
	include "Hypnosis/Dependencies/GLFW"
	include "Hypnosis/Dependencies/GLAD"
	include "Hypnosis/Dependencies/ImGui"
	include "Hypnosis/Dependencies/Assimp"
	group ""

include "Hypnosis"
include "Hypnosis Editor"
