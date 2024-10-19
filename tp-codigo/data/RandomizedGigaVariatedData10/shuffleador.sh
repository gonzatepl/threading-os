for j in $(seq "$1")
    do
        sort -R GigaRandomVariatedData_${j} > RandomizedGigaVariatedData_${j}
    done
