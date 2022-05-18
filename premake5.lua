workspace "absGL"
	architecture "x64"

	configurations {

		"Debug",
		"Release",
		"Dist",

	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "absGL"
	location "absGL"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {

		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
	}

	includedirs {
		"%{prj.name}/src",
		"deps/opengl/include",
		"deps/assimp/include",
		"deps/glm",
	}

	buildoptions "/MDd"

	libdirs { 
		"deps/opengl/libs",
		"deps/assimp/libs",
	}

	links {

		"glfw3",
		"opengl32",
		"assimp",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

		defines {

			"ABSGL_WINDOWS",
			"ABSGL_BUILD_DLL",
			"STB_IMAGE_IMPLEMENTATION",

		}

		postbuildcommands {

			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/experimental")

		}

	filter "configurations:Debug"
		defines "ABSGL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ABSGL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ABSGL_DEBUG"
		optimize "On"

project "experimental"
	location "experimental"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {

		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",

	}

	includedirs {

		"absGL/src",
		"deps/opengl/include",
		"deps/assimp/include",
		"deps/glm",

	}

	buildoptions "/MDd"

	libdirs { "deps/opengl/libs"}

	links {

		"absGL",
		"glfw3",
		"opengl32",

	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0"

		defines {

			"ABSGL_WINDOWS",

		}

	filter "configurations:Debug"
		defines "n3d_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "n3d_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "n3d_DEBUG"
		optimize "On"