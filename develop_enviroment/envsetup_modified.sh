cat <<EOF
使用方法
$ cgrep thename
$ cgrep -i thename
$ cgrep -E “\<thename\>”
$ cgrep -i -E “\<thename\>”
EOF

function cgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name *.o -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -exec grep --color -n "$@" {} +
}

function agrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name *.o -prune -o -type f -exec grep --color -n "$@" {} +
}

function nocgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name *.o -prune -o -name '*.c' -prune -o -name '*.cc' -prune -o -name '*.cpp' -prune -o -name '*.h' -prune -o -name '*.hpp' -prune -o -type f \
        -exec grep --color -n "$@" {} +
}

