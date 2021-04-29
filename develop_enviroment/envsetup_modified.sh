function cgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name out -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -exec grep --color -n "$@" {} +
}

function cgrepi()
{
    find . -name .repo -prune -o -name .git -prune -o -name out -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -exec grep --color -n -i "$@" {} +
}

function agrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name out -prune -o -type f -exec grep --color -n "$@" {} +
}

function agrepi()
{
    find . -name .repo -prune -o -name .git -prune -o -name out -prune -o -type f -exec grep --color -n -i "$@" {} +
}
