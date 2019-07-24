#!/bin/bash
if [[ -z $1 ]]
then
    echo -e "\033[31mOut of map's name.\033[0m"
    exit
else
    if [[ -z $2 ]]
    then
        echo -e "\033[31mOut of dump cycle.\033[0m"
        exit
    else
        for ((i = $2; ; i++))
        do
            ./vm_champs/corewar -d $i $1 > cor_ex
            ./corewar -dump64 $i $1 > cor_our
            diff cor_ex cor_our > res
            if [[ -s res ]]
            then
                echo -e "\033[31mDiff on cycle $i\033[0m"
                cat res
                break
            fi
        done
    fi
fi