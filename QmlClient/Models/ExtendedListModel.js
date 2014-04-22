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
    for (var key in idToIndex) {
        if (idToIndex[key] >= base) {
            idToIndex[key] += shift;
        }
    }
}
