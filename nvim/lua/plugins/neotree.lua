return {
  "nvim-neo-tree/neo-tree.nvim",
  branch = "v3.x",
  dependencies = {
    "nvim-lua/plenary.nvim",
    "nvim-tree/nvim-web-devicons",
    "MunifTanjim/nui.nvim",
  },
  config = function()
    require("neo-tree").setup({
      close_if_last_window = true,
      enable_diagnostics = true,
      enable_git_status = true,
      git_status_async = true,

      filesystem = {
        group_empty_dirs = false,
        use_libuv_file_watcher = true,
        follow_current_file = {
          enabled = true,
        },
        filtered_items = {
          visible = false,
          hide_dotfiles = false,
          hide_gitignored = false,
        },
        -- CUSTOM TRASH COMMAND LOGIC
        commands = {
          trash = function(state)
            local node = state.tree:get_node()
            if node.type == 'message' then return end
            local path = node.path
            local inputs = require("neo-tree.ui.inputs")

            inputs.confirm("Are you sure you want to trash '" .. node.name .. "'?", function(confirmed)
              if not confirmed then return end

              if vim.fn.has("win32") == 1 then
                vim.fn.system({ "powershell", "-Command", "Remove-Item -Path '" .. path .. "' -Recycle" })
              else
                -- Requires 'trash-cli' or 'trash' utility installed on Linux/macOS
                vim.fn.system({ "trash", path })
              end

              require("neo-tree.sources.manager").refresh(state.name)
            end)
          end,
        },
      },

      default_component_configs = {
        indent = {
          with_markers = true,
          indent_marker = "│",
          last_indent_marker = "└",
        },
        icon = {
          folder_closed = "",
          folder_open = "",
          folder_empty = "󰜌",
          default = "󰈚",
        },
        git_status = {
          symbols = {
            added     = "✚",
            modified  = "",
            deleted   = "✖",
            renamed   = "󰁯",
            untracked = "",
            ignored   = "",
            unstaged  = "󰄱",
            staged    = "",
            conflict  = "",
          },
        },
      },

      window = {
        position = "left",
        width = 35,
        mappings = {
          ["<space>"] = "none",
          ["H"] = "toggle_hidden",
          ["l"] = "open",
          ["h"] = "close_node",
          ["P"] = { "toggle_preview", config = { use_float = true } },
          -- UPDATED MAPPINGS
          ["d"] = "trash",        -- Calls our new trash command
          ["D"] = "delete",       -- Keep Shift+D for permanent delete
          ["r"] = "rename",
          ["a"] = "add",
          ["c"] = "copy",
          ["m"] = "move",
          ["p"] = "paste_from_clipboard",
        },
      },
    })

    -- Keymaps
    vim.keymap.set('n', '<leader>e', ":Neotree filesystem toggle reveal left dir=./<CR>", {
      desc = "Explorer (Project)", silent = true
    })
    vim.keymap.set('n', '<leader>E', ":Neotree filesystem show left dir=~/<CR>", {
      desc = "Explorer (Home)", silent = true
    })

    -- Auto-close logic
    vim.api.nvim_create_autocmd("BufEnter", {
      group = vim.api.nvim_create_augroup("NeotreeAutoClose", { clear = true }),
      callback = function()
        if vim.bo.filetype ~= "neo-tree" and vim.api.nvim_buf_get_name(0) ~= "" then
          vim.cmd("Neotree close")
        end
      end,
    })
  end
}
