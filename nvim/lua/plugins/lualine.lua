return {
  'nvim-lualine/lualine.nvim',
  dependencies = { 'nvim-tree/nvim-web-devicons' },
  config = function()
    local mode_icons = {
      ['NORMAL']  = '󰭩 ',
      ['INSERT']  = '✍️ ',
      ['VISUAL']  = '🔍',
      ['V-LINE']  = '📏',
      ['V-BLOCK'] = '🧊',
      ['COMMAND'] = ' ',
      ['REPLACE'] = '🔄',
    }

    -- Custom color map
    local mode_colors = {
      ['NORMAL']  = { bg = '#ffde21', fg = '#000000' },
      ['INSERT']  = { bg = '#008000', fg = '#ffffff' },
      ['VISUAL']  = { bg = '#ffffe4', fg = '#000000' },
      ['V-LINE']  = { bg = '#ffffe4', fg = '#000000' },
      ['V-BLOCK'] = { bg = '#ffffe4', fg = '#000000' },
      ['REPLACE'] = { bg = '#ba0214', fg = '#ffffff' },
      ['COMMAND'] = { bg = '#00FF00', fg = '#000000' },
    }

    require('lualine').setup({
      options = {
        theme = 'ayu_dark',
        section_separators = { left = '', right = '' },
        component_separators = { left = ' ', right = ' ' },
        globalstatus = true,
      },
      sections = {
        lualine_a = {
          {
            'mode',
            fmt = function(str)
              local m_icon = mode_icons[str] or ''
              return m_icon .. " " .. str .. "  " .. ''
            end,
            -- This is the fix: A function that returns the color based on mode
            color = function()
              local mode = require('lualine.utils.mode').get_mode()
              return mode_colors[mode] or { bg = '#ffde21', fg = '#000000' }
            end,
          }
        },
        lualine_b = {
          { 'branch', icon = '' },
          { 'diff', symbols = { added = '➕', modified = '📝 ', removed = '🗑️' } }
        },
        lualine_c = {
          { 'filename', file_status = true, path = 1, symbols = { modified = ' 💾', readonly = '' } }
        },
        lualine_x = {
          -- Adding the DAP and LSP status we discussed earlier
          {
            function() return " " .. require('dap').status() end,
            cond = function() return package.loaded["dap"] and require('dap').status() ~= "" end,
            color = { fg = '#ff5555' },
          },
          {
            'diagnostics',
            symbols = { error = '🚫 ', warn = '⚠️ ', info = '💡 ', hint = '🧠 ' },
          },
          'filetype',
        },
        lualine_y = {
          { function() return "󰉸" end },
          'progress'
        },
        lualine_z = {
          { 'location' },
        },
      },
    })
  end
}
