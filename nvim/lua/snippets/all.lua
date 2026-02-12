local ls = require("luasnip")
local s = ls.snippet
local i = ls.insert_node
local fmt = require("luasnip.extras.fmt").fmt
local rep = require("luasnip.extras").rep


return {
  s("cmake_base", fmt([[
cmake_minimum_required(VERSION 3.15)
project({} VERSION 1.0)

# REQUIRED for Neovim LSP (clangd) and Debugger
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where your source files are
add_executable(main {})

# Example of using the project name variable
# add_executable({} {})
  ]], {
    i(1, "ProjectName"), -- {1}
    i(2, "src/main.cpp"), -- {2}
    rep(1),               -- {3} repeats ProjectName
    rep(2),               -- {4} repeats the path
  })),
}
