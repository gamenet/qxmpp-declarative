import QtQuick 1.1
import "./ModelHelper.js" as Js

Item {
    id: root

    property alias count: listModel.count
    property string idProperty: 'id'

    signal sourceChanged()

    function model() {
        return listModel;
    }

    function append(dict) {
        var index = 0;

        if (!dict)
            return;

        if (dict[root.idProperty] && dict.hasOwnProperty(root.idProperty)) {
            var key = dict[root.idProperty];

            if (Js.idToIndex.hasOwnProperty(key)) {
                index = Js.idToIndex[key];
                listModel.remove(index);
                listModel.insert(index, dict);
            } else {
                index = listModel.count;
                listModel.append(dict);
                Js.idToIndex[key] = index;
            }
        }
        d.sendSourceChanged();
    }

    function clear() {
        Js.idToIndex = {};
        listModel.clear();
        d.sendSourceChanged();
    }

    function contains(id) {
        return Js.idToIndex.hasOwnProperty(key);
    }

    function get(index) {
        return listModel.get(index);
    }

    function getById(id) {
        if (!Js.idToIndex.hasOwnProperty(id)) {
            return;
        }

        return listModel.get(Js.idToIndex[id]);
    }

    function getIndexById(id) {
        if (!Js.idToIndex.hasOwnProperty(id)) {
            return -1;
        }
        return Js.idToIndex[key];
    }

    //    function insert(at, dict) {
    //        var index = 0;

    //        if (at >= listModel.count) {
    //            append(dict);
    //            return;
    //        }

    //        if (dict[root.idProperty] && dict.hasOwnProperty(root.idProperty)) {
    //            if (Js.idToIndex.hasOwnProperty(key)) {
    //                index = Js.idToIndex[key];
    //                listModel.remove(index);

    //                listModel.insert(index, dict);
    //            } else {
    //                index = listModel.count;
    //                listModel.append(dict);
    //                Js.idToIndex[key] = index;
    //            }
    //        }
    //        listModel.insert(index, dict);
    //    }

    //    function remove(index) {
    //        // 10.12.2012 igor.bugaev
    //        // TODO - функция не работает, разобратся

    //        var obj = _model.get(index),
    //            key;

    //        if (!obj) {
    //            return;
    //        }

    //        key = obj[objectIdPropertyName];
    //        _model.remove(index); // падает здесь
    //        Helper.removeKey(key);
    //        d.sendSourceChanged();
    //    }

    function removeById(id) {
        var index;
        if (!Js.idToIndex.hasOwnProperty(id)) {
            return;
        }

        index = Js.idToIndex[id];
        listModel.remove(index);
        Js.removeId(id);
        d.sendSourceChanged();
    }

    function setProperty(index, name, value) {
        listModel.setProperty(index, name, value);
    }

    function setPropertyById(id, name, value) {
        console.log("setPropertyById for id == " + id + ", property: " + name + ", value: " + value);

        var index;
        if (!Js.idToIndex.hasOwnProperty(id)) {
            return;
        }

        index = Js.idToIndex[id];



        var obj = listModel.get(index);
        console.log("current: " + obj[name])

        listModel.setProperty(index, name, value);
        obj = listModel.get(index);
        console.log("after: " + obj[name])
    }

    QtObject {
        id: d

        property bool canSendSourceChanged: true;

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
