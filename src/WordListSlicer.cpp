#include "WordListSlicer.h"

std::vector<WordList> WordListSlicer::slice(WordList &wl, size_t slices) const
{

    if (wl.empty() || slices == 0 || slices > wl.size()) {
        return {};
    }

    std::vector<WordList> result;
    size_t total_size = wl.size();
    size_t slice_size = total_size / slices;
    size_t remainder = total_size % slices;

    auto it = wl.begin();
    for (size_t i = 0; i < slices; ++i) {
        size_t current_slice_size = slice_size + (i < remainder ? 1 : 0);

        auto slice_range =
            std::ranges::subrange(it, std::next(it, current_slice_size));

        result.emplace_back(slice_range.begin(), slice_range.end());

        std::advance(it, current_slice_size);
    }

    return result;
}
