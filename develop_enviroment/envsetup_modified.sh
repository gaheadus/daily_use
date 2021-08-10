cat <<EOF
说明：这里的函数定义只在原有命令的基础上增加了一些过滤条件，保持原有grep、find的语法，使用方法和原有grep、find一样。
例：
$ cgrep thename
$ cgrep -i thename
$ cgrep -E “\<thename\>”
$ cgrep -i -E “\<thename\>”
$ ffind -name thename -type f
EOF

function cgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -exec grep --color -n "$@" {} +
}

function agrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f -exec grep --color -n "$@" {} +
}

function nocgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -name '*.c' -prune -o -name '*.cc' -prune -o -name '*.cpp' -prune -o -name '*.h' -prune -o -name '*.hpp' -prune -o -type f \
        -exec grep --color -n "$@" {} +
}

function mgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o \( -regextype posix-egrep -iregex '(.*\/Makefile|.*\/Makefile\..*|.*\.make|.*\.mak|.*\.mk|.*\.bp)' -o -regextype posix-extended -regex '(.*/)?soong/[^/]*.go' \) -type f \
        -exec grep --color -n "$@" {} +
}

function ffind()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o "$@" -print
}