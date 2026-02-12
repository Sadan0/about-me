return {
  'Civitasv/cmake-tools.nvim',
  dependencies = { 'nvim-lua/plenary.nvim' },
  -- Trigger: Only load when one of these keys is pressed
  keys = {
    { "<leader>cg", ":CMakeGenerate<cr>", desc = "CMake: [G]enerate" },
    { "<leader>cb", ":CMakeBuild<cr>",    desc = "CMake: [B]uild" },
    { "<leader>cd", ":CMakeDebug<cr>",    desc = "CMake: [D]ebug (Project)" },
    { "<leader>cs", ":CMakeSelectLaunchTarget<cr>", desc = "CMake: [S]elect Target" },
  },
  opts = {
    cmake_build_directory = "build/${variant:buildType}",
    cmake_generate_options = { "-DCMAKE_EXPORT_COMPILE_COMMANDS=1" },
    cmake_dap_configuration = {
      type = "codelldb",
      request = "launch",
      stopOnEntry = false,
      runInTerminal = false,
    },
  }
}
