# vim configuration file

A good `.vimrc` in your home directory helps a lot to use vim effectively.

Lines starting with `"` are comments, lines starting with `:` are commands
that set up vim.

```
" make vim recognize files of various types for type specific stuff
:filetype on
" all files can be smartindented
:set smartindent
" but files with a C-like syntax are cindented
:autocmd FileType c,cpp,h,java :set cindent
" do syntax highlighting
:syntax on

" show line number, since this simplifies G-jumping
:set number

" no tabs for indentation, and indent should be 4 spaces
:set expandtab
:set tabstop=4
:set shiftwidth=4

" create file~ backups
:set backup

" highlight the cursor line, so that one sees where one is about to type
:set cursorline
:hi CursorLine cterm=NONE ctermbg=cyan ctermfg=black guibg=cyan guifg=black

" show a status line with 
"   t: file name
"   y: file type
"   ff: format (DOS/Unix/...)
"   l,c: line and column number
"   r: read-only status
:set laststatus=2
:set statusline=%t\ %y\ %{&ff}\ (%l,%c)\ %r

" make sure views are auto-saved/loaded so that folds are preserved
" between edit sessions
au BufWinLeave ?* mkview
au BufWinEnter ?* silent loadview

" set color scheme
:colorscheme desert

" make sure some lines above or below current line are visible at all times
:set scrolloff=5
```
