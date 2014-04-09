var idToIndex = {};

function insertId(index, id) {
    if (idToIndex.hasOwnProperty(id)) {
        removeId(id);
    }
    shiftIndexes(index, 1);
    idToIndex[id] = index;
}

function removeId(id) {
    var index;
    if (!idToIndex.hasOwnProperty(id)) {
        return;
    }

    index = idToIndex[id];
    delete idToIndex[id];
    shiftIndexes(index, -1);
}

function shiftIndexes(base, shift) {
    for (var link in idToIndex) {
        if (idToIndex[link] > base) {
            idToIndex[link] += shift;
        }
    }
}
