cat $(find test_results -name "*should*") | grep died | wc -l && find test_results -name "*should*" | wc -l

cat $(find test_results -name "*not*") | grep died | wc -l
