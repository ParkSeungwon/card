let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/Programming/card
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 ~/Programming/card/card.h
badd +1 ~/Programming/card/card.cpp
badd +1 ~/Programming/card/card.cc
badd +1 ~/Programming/card/poker.cpp
badd +1 ~/Programming/card/hand5.cc
badd +1 ~/Programming/card/Makefile
badd +1 ~/Programming/card/deck.cc
badd +1 ~/Programming/card/combi.h
badd +1 ~/Programming/card/combi.cc
badd +1 ~/Programming/card/hand5.h
badd +1 ~/Programming/card/game.h
badd +1 ~/Programming/card/game.cc
badd +1 ~/Programming/card/test.cpp
badd +1 ~/Programming/card/hand.h
badd +0 ~/Programming/card/hand7.h
badd +1 ~/Programming/card/hand.cc
badd +0 ~/Programming/card/hand7.cc
badd +0 ~/Programming/card/player.h
badd +0 ~/Programming/card/player.cc
argglobal
silent! argdel *
set stal=2
edit ~/Programming/card/card.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 31 - ((24 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
31
normal! 050|
tabedit ~/Programming/card/card.cc
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 34 - ((33 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
34
normal! 032|
tabedit ~/Programming/card/poker.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 22 - ((21 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
22
normal! 051|
tabedit ~/Programming/card/game.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 14 - ((13 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
14
normal! 010|
tabedit ~/Programming/card/game.cc
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 127 - ((24 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
127
normal! 023|
tabedit ~/Programming/card/test.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 16 - ((15 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
16
normal! 017|
tabedit ~/Programming/card/deck.cc
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 8 - ((7 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
8
normal! 017|
tabedit ~/Programming/card/hand.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabedit ~/Programming/card/hand.cc
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabedit ~/Programming/card/player.h
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabedit ~/Programming/card/player.cc
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 23) / 46)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabnext 11
set stal=1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
