from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy
import os

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
        self.requires("imgui/cci.20230105+1.89.2.docking")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        imgui_info = self.dependencies["imgui"].cpp_info
        # self.output.info("**libs:{}**".format())
        copy(self, "imgui_impl_glfw.*", imgui_info.srcdirs[0], f"{self.source_path}\\thirdparty\\imgui_bindings")
        copy(self, "imgui_impl_opengl3.*", imgui_info.srcdirs[0], f"{self.source_path}\\thirdparty\\imgui_bindings")
        copy(self, "imgui_impl_opengl3_loader.h", imgui_info.srcdirs[0], f"{self.source_path}\\thirdparty\\imgui_bindings")