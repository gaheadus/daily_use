#!/bin/bash
#说明：这里的函数定义只在原有命令的基础上增加了一些过滤条件，保持原有grep、find的语法，使用方法和原有grep、find一样。Copy right@dukang
#例：
# cgrep thename
# cgrep -i thename
# cgrep -E “\<thename\>”
# cgrep -i -E “\<thename\>”
# ffind -name thename -type f

#版本一：使用exec，注意末尾加'{} +'
function cgrep()
{
    find . -name 'work_dir*' -prune -o -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -exec grep -a --color -n "$@" {} +
}
#版本二：使用xargs，注意'| xargs grep'的前面要假'-print'
function cgrep2()
{
    find . -name 'work_dir*' -prune -o -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -print | xargs grep -a --color -n "$@"
}
#经测试，速度上-exec command {} +最快，-print|xargs command次之，-exec command {} \;最慢。20210822

function agrep()
{
    find . -name 'work_dir*' -prune -o -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f -exec grep -a --color -n "$@" {} +
}

function nocgrep()
{
    find . -name 'work_dir*' -prune -o -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -name '*.c' -prune -o -name '*.cc' -prune -o -name '*.cpp' -prune -o -name '*.h' -prune -o -name '*.hpp' -prune -o -type f \
        -exec grep -a --color -n "$@" {} +
}

function mgrep()
{
    find . -name 'work_dir*' -prune -o -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o \( -regextype posix-egrep -iregex '(.*\/Makefile|.*\/Makefile\..*|.*\.make|.*\.mak|.*\.mk|.*\.bp)' -o -regextype posix-extended -regex '(.*/)?soong/[^/]*.go' \) -type f \
        -exec grep -a --color -n "$@" {} +
}

function ffind()
{
    find . -name 'work_dir*' -prune -o -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o "$@" -print
}



# 包含work_dir搜索
function wcgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) \
        -exec grep -a --color -n "$@" {} +
}

function wagrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -type f -exec grep -a --color -n "$@" {} +
}

function wnocgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o -name '*.c' -prune -o -name '*.cc' -prune -o -name '*.cpp' -prune -o -name '*.h' -prune -o -name '*.hpp' -prune -o -type f \
        -exec grep -a --color -n "$@" {} +
}

function wmgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o -name '*.o' -prune -o \( -regextype posix-egrep -iregex '(.*\/Makefile|.*\/Makefile\..*|.*\.make|.*\.mak|.*\.mk|.*\.bp)' -o -regextype posix-extended -regex '(.*/)?soong/[^/]*.go' \) -type f \
        -exec grep -a --color -n "$@" {} +
}

function wffind()
{
    find . -name .repo -prune -o -name .git -prune -o -name .svn -prune -o -name out -prune -o "$@" -print
}

function m3sync(){
    echo "cp ../UGW_main/work_dir.bcm6756_11ax_nor_mesh3.0/vendor/release/bcm6756_11ax_nor_mesh3.0_release.bz2 platform"
          cp ../UGW_main/work_dir.bcm6756_11ax_nor_mesh3.0/vendor/release/bcm6756_11ax_nor_mesh3.0_release.bz2 platform
    echo "cp ../UGW_main/work_dir.bcm6756_11ax_nor_mesh3.0/cbb/wifi/bcm6756_11ax_nor_mesh3.0_wifi_release.bz2 platform"
          cp ../UGW_main/work_dir.bcm6756_11ax_nor_mesh3.0/cbb/wifi/bcm6756_11ax_nor_mesh3.0_wifi_release.bz2 platform
}


function m2sync(){
    echo "cp ../UGW_main/work_dir.bcm6756_11ax_nor/vendor/release/bcm6756_11ax_nor_release.bz2 platform"
    cp ../UGW_main/work_dir.bcm6756_11ax_nor/vendor/release/bcm6756_11ax_nor_release.bz2 platform
    echo "cp ../UGW_main/work_dir.bcm6756_11ax_nor/cbb/wifi/bcm6756_11ax_nor_wifi_release.bz2 platform"
    cp ../UGW_main/work_dir.bcm6756_11ax_nor/cbb/wifi/bcm6756_11ax_nor_wifi_release.bz2 platform
}


function repo2()
{
    cmds=("status" "log" "branch" "sync" "checkout" "start" "pull" "forall")
    i=1

    for cmd in ${cmds[@]}; do
        if [ "$1" == $cmd ]; then
            #echo "current command is $cmd, total cmd num=${#cmds[@]}"
            break
        fi
        let i++
    done

    if [ $i -gt ${#cmds[@]} ]; then
        echo "command $1 NOT support!!!"
        return 1
    fi


    curdir=`pwd`
    oldpwd=$OLDPWD

    while true; do
        if [ -f PLATFORM_TOP.flag ]; then
            PROJ_TOP=`pwd`
            break
        else
            cd ..
            if [ "`pwd`" == "/" ]; then
                echo "NOT in a UGW_main project repository !!!"
                cd $curdir
                OLDPWD=$oldpwd
                unset PROJ_TOP
                return 2
            fi
        fi
    done


    subcmd=$*
    only_cur_dir=0

    if [ "$1" == "sync" ]; then
        subcmd="pull --rebase"
    fi

    if [ "$1" == "start" ]; then
        if [ "$#" -ne 2 ] && [ "$#" -ne 3 ]; then
            echo "syntax error !!! input param num=$#"
            return 3
        else
            remote_br=`git branch -r | grep HEAD | awk '{print $3}'`
            subcmd="checkout -b $2 $remote_br"

            if [ "$#" -eq 2 ]; then
                only_cur_dir=1
            fi

            if [ "$#" -eq 3 ] && [ "$3" != "--all" ]; then
                echo "syntax error !!! input param 3 error"
                return 4
            fi

        fi
    fi

    if [ "$1" == "log" ];then
        if [ "$#" -eq 1 -o "$#" -eq 2 ];then
            if [ "$#" -eq 2 ]; then
                if [ "$2" != "-1" ] && [ "$2" != "-2" ]; then
                    echo "only 1 or 2 commit log support !!!"
                    return 5
                fi
            else
                subcmd="log -1"
            fi
        else
            echo "too many input paramters !!!"
            return 6
        fi
    fi

    real_cmd="git $subcmd"
    if [ "$1" == "forall" ]; then
        if [ "$2" != "-c" ]; then
            echo "Usage: repo forall -c command"
            return 6
        fi
        shift 2
        real_cmd=$*
    fi

    auto_chan_bw_select="cbb/wifi/auto_chan_bw_select"
    mesh3="cbb/mesh3.0"
    Tenda_Easymesh="cbb/mesh/Tenda_Easymesh"
    Tenda_Xmesh="cbb/mesh/Tenda_Xmesh"
    vendor="vendor"
    #dirs=($auto_chan_bw_select $mesh3 $Tenda_Easymesh $Tenda_Xmesh $vendor "/") #注：使用"/"或"."，如果写成""，空字符串在for循环中会被优化掉
    dirs=($auto_chan_bw_select $mesh3 $Tenda_Easymesh $Tenda_Xmesh $vendor)

    if [ $only_cur_dir == 1 ]; then
        $real_cmd
        echo
    else
        for dir in ${dirs[@]}; do
            echo $PROJ_TOP/$dir
            cd $PROJ_TOP/$dir
            $real_cmd
            echo
        done

        #空字符串""在for循环中会被优化掉，PROJ_TOP只能单独写。写成"/"或"."也可以，但是风格不统一，显示效果不好。
        echo $PROJ_TOP
        cd $PROJ_TOP
        $real_cmd
        echo

        cd $curdir
        OLDPWD=$oldpwd
    fi

    unset real_cmd
    unset subcmd
    unset remote_br
    unset PROJ_TOP
    unset curdir
}
