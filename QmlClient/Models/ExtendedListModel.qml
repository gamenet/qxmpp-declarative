import QtQuick 1.1
import "./ExtendedListModel.js" as ExtendedListModelJs

Item {
    id: root

    property alias model: listModel
    property alias count: listModel.count
    property string idProperty: 'id'

    signal sourceChanged()

    function append(dict) {
        var index = 0;

        if (!dict)
            return;

        if (dict[root.idProperty] && dict.hasOwnProperty(root.idProperty)) {
            var key = dict[root.idProperty];

            if (ExtendedListModelJs.idToIndex.hasOwnProperty(key)) {
                index = ExtendedListModelJs.idToIndex[key];
                ExtendedListModelJs.removeId(key);
                listModel.remove(index);
                ExtendedListModelJs.idToIndex[key] = listModel.count;
                listModel.append(dict);
            } else {
                index = listModel.count;
                listModel.append(dict);
                ExtendedListModelJs.idToIndex[key] = index;
            }
        }
        d.sendSourceChanged();
    }

    function clear() {
        ExtendedListModelJs.idToIndex = {};
        listModel.clear();
        d.sendSourceChanged();
    }

    function contains(id) {
        return ExtendedListModelJs.idToIndex.hasOwnProperty(id);
    }

    function get(index) {
        return listModel.get(index);
    }

    function getById(id) {
        if (!ExtendedListModelJs.idToIndex.hasOwnProperty(id)) {
            return;
        }

        return listModel.get(ExtendedListModelJs.idToIndex[id]);
    }

    function getIndexById(id) {
        if (!ExtendedListModelJs.idToIndex.hasOwnProperty(id)) {
            return -1;
        }
        return ExtendedListModelJs.idToIndex[id];
    }

    function insert(at, dict) {
        var index = 0;
        var key;

        if (at >= listModel.count) {
            root.append(dict);
            return;
        }

        if (dict[root.idProperty] && dict.hasOwnProperty(root.idProperty)) {
            key = dict[root.idProperty];

            if (ExtendedListModelJs.idToIndex.hasOwnProperty(key)) {
                //  already exists
                return;
            }

            ExtendedListModelJs.insertId(at, key);
            listModel.insert(at, dict);
        }
    }

    function remove(index) {
        var obj = listModel.get(index);
        var key;

        if (!obj) {
            return;
        }

        key = obj[root.idProperty];

        model.remove(index);
        ExtendedListModelJs.removeId(key);
        d.sendSourceChanged();
    }

    function removeById(id) {
        var index;
        if (!ExtendedListModelJs.idToIndex.hasOwnProperty(id)) {
            return;
        }

        index = ExtendedListModelJs.idToIndex[id];
        listModel.remove(index);
        ExtendedListModelJs.removeId(id);
        d.sendSourceChanged();
    }

    function getProperty(index, name) {
        var item;

        if (index < 0 || index >= listModel.count) {
            return;
        }

        item = listModel.get(index);
        return item[name];
    }

    function getPropertyById(id, name) {
         var item;

        if (!ExtendedListModelJs.idToIndex.hasOwnProperty(id)) {
            return;
        }

        item = listModel.get(ExtendedListModelJs.idToIndex[id]);
        return item[name];
    }

    function setProperty(index, name, value) {
        if (index < 0 || index >= listModel.count) {
            return;
        }

        listModel.setProperty(index, name, value);
    }

    function setPropertyById(id, name, value) {
        var index;
        if (!ExtendedListModelJs.idToIndex.hasOwnProperty(id)) {
            return;
        }

        index = ExtendedListModelJs.idToIndex[id];

        var obj = listModel.get(index);

        listModel.setProperty(index, name, value);
        obj = listModel.get(index);
    }

    function getColumn(columnName) {
        var result = [];

        var count = listModel.count;
        var obj;
        for(var i = 0; i < count; i++){
            obj = listModel.get(i);
            result.push(obj[columnName]);
        }
        return result;
    }

    function sortByColumn(columnName, sortFunction)
    {
        var sortFn = sortFunction || ascending;
        var sortdata = [];

        for (var i = 0; i < listModel.count; ++i) {
            var itemId = listModel.get(i).toString();
            var obj = listModel.get(i);

            if (obj[columnName] != undefined) {
                sortdata[i] = {
                    id: itemId,
                    value: obj[columnName]
                };
            } else {
                console.log("Field '" + columnName + "' not found in item " + itemId);
                return;
            }

        }
        sortdata.sort(sortFn);

        for (var i = 0; i < sortdata.length; ++i) {
            for (var j = 0; j < listModel.count; ++j){
                if (listModel.get(j).toString() === sortdata[i].id) {
                    listModel.move(j, listModel.count - 1, 1);
                    break;
                }
            }
        }
    }

    function ascending(a, b) {
        if (a.value > b.value) {
            return 1;
        }
        return -1;
    }

    function descending(a, b) {
        if (a.value < b.value) {
            return 1;
        }
        return -1;
    }

    QtObject {
        id: d

        property bool canSendSourceChanged: true

        function sendSourceChanged() {
            if (canSendSourceChanged) {
                root.sourceChanged();
            }
        }
    }

    ListModel {
     id: listModel
    }
}
