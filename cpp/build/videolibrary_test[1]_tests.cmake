add_test( VideoLibrary.VideoLibraryHasAllVideos /Users/beep_kai/google-code-sample/cpp/build/videolibrary_test [==[--gtest_filter=VideoLibrary.VideoLibraryHasAllVideos]==] --gtest_also_run_disabled_tests)
set_tests_properties( VideoLibrary.VideoLibraryHasAllVideos PROPERTIES WORKING_DIRECTORY /Users/beep_kai/google-code-sample/cpp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( VideoLibrary.VideoLibraryParsesTagsCorrectly /Users/beep_kai/google-code-sample/cpp/build/videolibrary_test [==[--gtest_filter=VideoLibrary.VideoLibraryParsesTagsCorrectly]==] --gtest_also_run_disabled_tests)
set_tests_properties( VideoLibrary.VideoLibraryParsesTagsCorrectly PROPERTIES WORKING_DIRECTORY /Users/beep_kai/google-code-sample/cpp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test( VideoLibrary.testLibraryParsesVideoCorrectlyWithoutTags /Users/beep_kai/google-code-sample/cpp/build/videolibrary_test [==[--gtest_filter=VideoLibrary.testLibraryParsesVideoCorrectlyWithoutTags]==] --gtest_also_run_disabled_tests)
set_tests_properties( VideoLibrary.testLibraryParsesVideoCorrectlyWithoutTags PROPERTIES WORKING_DIRECTORY /Users/beep_kai/google-code-sample/cpp/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( videolibrary_test_TESTS VideoLibrary.VideoLibraryHasAllVideos VideoLibrary.VideoLibraryParsesTagsCorrectly VideoLibrary.testLibraryParsesVideoCorrectlyWithoutTags)
