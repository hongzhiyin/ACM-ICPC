se nu si mouse=a ts=4 sts=4 sw=4 fdm=marker et
nm<F2> : vs %<.in <CR>                                       " 新建输入文件
nm<F3> : !gedit % <CR>                                       " 用 gedit 打开
nm<F5> : !./%< <CR>                                          " 在命令行中运行
nm<F8> : !time ./%< < %<.in <CR>                             " 文件运行，显示运行时间
nm<F9> : :w <CR> :make %< <CR>                               " 保存并编译
nm<F7> : :w <CR> :!g++ % -o %< -O2 -g -std=c++11 -Wall <CR>  " 保存并编译（优化）
nm<F12> ggvGd:r head.cpp <CR> kdd
