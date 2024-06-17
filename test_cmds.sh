cat $(find /tmp/test_results -name "*should*") | grep died | wc -l && find /tmp/test_results -name "*should*" | wc -l

cat $(find /tmp/test_results -name "*not*") | grep died | wc -l
