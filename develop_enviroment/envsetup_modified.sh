cat <<EOF
说明：这里的函数定义只在原有命令的基础上增加了一些过滤条件，保持原有grep、find的语法，使用方法和原有grep、find一样。
例：
$ cgrep thename
$ cgrep -i thename
$ cgrep -E “\<thename\>”
$ cgrep -i -E “\<thename\>”
$ ffind -name thename -type f
EOF

#版本一：使用exec，注意末尾加'{} +'
function cgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -exec grep -a --color -n "$@" {} +
}
#版本二：使用xargs，注意'| xargs grep'的前面要假'-print'
function cgrep2()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -print | xargs grep -a --color -n "$@"
}
#经测试，速度上-exec command {} +最快，-print|xargs command次之，-exec command {} \;最慢。20210822

function agrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f -exec grep -a --color -n "$@" {} +
}

function nocgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -name '*.c' -prune -o -name '*.cc' -prune -o -name '*.cpp' -prune -o -name '*.h' -prune -o -name '*.hpp' -prune -o -type f \
        -exec grep -a --color -n "$@" {} +
}

function mgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o \( -regextype posix-egrep -iregex '(.*\/Makefile|.*\/Makefile\..*|.*\.make|.*\.mak|.*\.mk|.*\.bp)' -o -regextype posix-extended -regex '(.*/)?soong/[^/]*.go' \) -type f \
        -exec grep -a --color -n "$@" {} +
}

function ffind()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o "$@" -print
}
