from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps


class ProjectTeletrackSimRecipe(ConanFile):
    name = "project_teletrack_sim"
    version = "0.0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        # you can add more Conan packages here when you need them:
        # self.requires("catch2/3.4.0")
        # self.requires("fmt/10.1.1")
        # self.requires("sfml/2.6.1")
        # self.requires("poco/1.13.3")
        self.requires("gtest/1.14.0")
