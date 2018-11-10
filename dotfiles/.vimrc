set nocompatible              " be iMproved, required
set number
colorscheme elflord
set showcmd
set hlsearch

" split new window to below
set splitbelow

set tabstop=4
set softtabstop=4
set shiftwidth=4
" tab to space
set expandtab

filetype on                  " required

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'bling/vim-airline'
"Plugin 'tpope/vim-fugitive'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }
Plugin 'junegunn/fzf.vim'

" code formatting
Plugin 'google/vim-maktaba'
Plugin 'google/vim-codefmt'
Plugin 'google/vim-glaive'

call vundle#end()            " required

call glaive#Install()

filetype plugin indent on    " required
inoremap <A-h> <C-o>h
inoremap <A-j> <C-o>j
inoremap <A-k> <C-o>k
inoremap <A-l> <C-o>l

"buffer movement with arrows
nnoremap <silent> <C-Right> <c-w>l
nnoremap <silent> <C-Left> <c-w>h
nnoremap <silent> <C-Up> <c-w>k
nnoremap <silent> <C-Down> <c-w>j

"Code formatting
noremap <C-F> :FormatLines<CR>

set t_Co=256
set laststatus=2
let g:airline_detect_paste=1
let g:airline#extensions#tabline#enabled = 1
set ttimeoutlen=50
