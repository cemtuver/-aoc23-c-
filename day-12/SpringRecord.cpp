#include <vector>

using namespace std;

struct SpringRecord {
    string record;
    vector<int> contiguousGroups;
};

SpringRecord parseSpringRecord(const string& input, int expansionFactor) {
    SpringRecord springRecord;
    vector<string> parts = input::split(input, " ");
    vector<int> contiguousGroups = input::splitInt(parts.at(1), ",");

    springRecord.record = parts.at(0);
    springRecord.contiguousGroups = contiguousGroups;

    for (int i = 0; i < expansionFactor - 1; i++) {
        springRecord.record += "," + parts.at(0);
        springRecord.contiguousGroups.insert(
            springRecord.contiguousGroups.end(), 
            contiguousGroups.begin(), 
            contiguousGroups.end()
        );
    }

    return springRecord;
}

long long findNumberOfPossibleSolutions(
    unordered_map<string, long long>& cache, 
    const string& record, 
    const vector<int>& contiguousGroups, 
    int ir, 
    int ic
) {
    long long sum = 0;
    string cacheKey = to_string(ir) + ":" + to_string(ic);
    
    if (cache.find(cacheKey) != cache.end()) {
        return cache[cacheKey];
    }
    
    if (ir >= record.length()) {
        return ic == contiguousGroups.size() ? 1 : 0;
    }

    if (record.at(ir) != '#') {
        sum += findNumberOfPossibleSolutions(cache, record, contiguousGroups, ir + 1, ic);
    }

    if (
        (record.at(ir) != '.' && ic < contiguousGroups.size()) &&
        (ir + contiguousGroups[ic] <= record.length() && record.substr(ir, contiguousGroups.at(ic)).find('.') == -1) &&
        (ir + contiguousGroups[ic] == record.length() || record[ir + contiguousGroups.at(ic)] != '#')
    ) {
        sum += findNumberOfPossibleSolutions(cache, record, contiguousGroups, ir + contiguousGroups[ic] + 1, ic + 1);
    }

    cache[cacheKey] = sum;
    return sum;
}
