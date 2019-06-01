empty_binary="empty"
supp_file="my_supp.supp"

gcc -o $empty_binary empty.c
valgrind --leak-check=full --gen-suppressions=all "./${empty_binary}" 2>&1 | perl supp_getter.perl > $supp_file
rm $empty_binary
rm -rf "${empty_binary}.dSYM"
