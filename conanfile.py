from conan import ConanFile
from conan.tools.cmake import cmake_layout

class ProjectConanRecipe(ConanFile):
    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("fmt/[~9.1]")
        self.requires("glew/[~2.2]")
        self.requires("glfw/[~3.3]")
        self.requires("glm/cci.20230113")
        self.requires("stb/cci.20220909")

    def layout(self):
        cmake_layout(self)
