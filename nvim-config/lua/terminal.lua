local M = {}
local term_buf = nil


-- 1. Define the Green Highlight (Nord-compatible Green)
vim.api.nvim_set_hl(0, "TerminalBorder", { fg = "#A3BE8C", bold = true })


M.toggle_terminal = function()
    -- Get current directory to keep terminal synced with your file
    local current_dir = vim.fn.expand('%:p:h')
    if current_dir == "" or current_dir == "." then current_dir = vim.fn.getcwd() end

    -- Check if terminal window is already open; if so, close it (hide)
    if term_buf and vim.api.nvim_buf_is_valid(term_buf) then
        local term_win = vim.fn.bufwinnr(term_buf)
        if term_win > -1 then
            vim.api.nvim_win_close(vim.fn.win_getid(term_win), true)
            return
        end
    end

    -- Create the split at the bottom
    vim.cmd("botright 10split")
    -- 2. Apply the Green Border/Separator for this window
    vim.opt_local.winhighlight = "WinSeparator:TerminalBorder"

    if term_buf and vim.api.nvim_buf_is_valid(term_buf) then
        -- Re-use existing buffer
        vim.api.nvim_win_set_buf(0, term_buf)
        local chan_id = vim.b[term_buf].terminal_job_id
        if chan_id then
            -- Sync directory every time it opens
            vim.api.nvim_chan_send(chan_id, " cd " .. current_dir .. " && clear\n")
        end
    else
        -- Create new terminal session
        vim.cmd("term")
        term_buf = vim.api.nvim_get_current_buf()
        vim.bo[term_buf].buflisted = false
    end

    -- 3. UI Cleanup (Ensure terminal is clean)
    vim.opt_local.number = false
    vim.opt_local.relativenumber = false
    vim.opt_local.signcolumn = "no"
    vim.opt_local.foldcolumn = "0" -- Ensure your fold logic doesn't show up here
    vim.cmd("startinsert")
end

return M
