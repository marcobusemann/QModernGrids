#include <QtTest>

#include <QModernGrids/QmgObservableList.h>

class QmgObservableListTest : public QObject
{
   Q_OBJECT

private Q_SLOTS:

   void size_listIsEmpty_zero()
   {
      QmgObservableList<int> list;

      QCOMPARE(list.size(), 0);
   }

   void size_listHasOneElement_one()
   {
      QmgObservableList<int> list;
      list.append(10);

      QCOMPARE(list.size(), 1);
   }

   void isEmpty_listIsEmpty_true()
   {
      QmgObservableList<int> list;

      QCOMPARE(list.isEmpty(), true);
   }

   void isEmpty_listHasOneElement_false()
   {
      QmgObservableList<int> list;
      list.append(10);

      QCOMPARE(list.isEmpty(), false);
   }

   void clear_listIsEmpty_listIsEmpty()
   {
      QmgObservableList<int> list;

      list.clear();

      QCOMPARE(list.isEmpty(), true);
   }

   void clear_listHasOneElement_listIsEmpty()
   {
      QmgObservableList<int> list;
      list.append(10);

      list.clear();

      QCOMPARE(list.isEmpty(), true);
   }

   void append_listIsEmpty_oneElement()
   {
      QmgObservableList<int> list;

      list.append(10);

      QCOMPARE(list.size(), 1);
      QCOMPARE(list.at(0), 10);
   }

   void insert_listIsEmpty_oneElement()
   {
      QmgObservableList<int> list;

      list.insert(0, 10);

      QCOMPARE(list.size(), 1);
      QCOMPARE(list.at(0), 10);
   }

   void removeAt_oneItem_zeroItems()
   {
      QmgObservableList<int> list;
      list.append(10);

      list.removeAt(0);

      QCOMPARE(list.size(), 0);
   }

   void update_oneItemAtIndex0_updatedItemAtIndex0()
   {
      QmgObservableList<int> list;
      list.append(10);

      list.update(0, 15);

      QCOMPARE(list.at(0), 15);
   }

   void indexOf_listIsEmpty_minusOne()
   {
      QmgObservableList<int> list;

      QCOMPARE(list.indexOf(10), -1);
   }

   void indexOf_listHasOneElement_indexOfThatElement()
   {
      QmgObservableList<int> list;
      list.append(10);

      QCOMPARE(list.indexOf(10), 0);
   }

   void indexOf_listHasThreeElementsSearchTheMiddleOne_indexOfTheMiddleOne()
   {
      QmgObservableList<int> list;
      list.append(5);
      list.append(10);
      list.append(15);

      QCOMPARE(list.indexOf(10), 1);
   }

   void indexOf_listHasThreeElementsSearchedIsTwoTimesPresentStartAtIndexOfPlusOne_IndexOfSecond()
   {
      QmgObservableList<int> list;
      list.append(10);
      list.append(5);
      list.append(10);

      QCOMPARE(list.indexOf(10, 1), 2);
   }

   void empty_emptyList()
   {
      auto list = QmgObservableList<int>::empty();

      QCOMPARE(list.size(), 0);
   }

   void fromList_QListWithTwoElements_ObservableListWithTheSameElements()
   {
      auto sourceList = QList<int>() << 5 << 10;

      auto list = QmgObservableList<int>::fromList(sourceList);

      QCOMPARE(list.at(0), 5);
      QCOMPARE(list.at(1), 10);
   }

   void fromList_ObservableLIstWithTwoElements_ObservableListWithTheSameElements()
   {
      auto sourceList = QmgObservableList<int>::empty();
      sourceList.append(5);
      sourceList.append(10);

      auto list = QmgObservableList<int>::fromList(sourceList);

      QCOMPARE(list.at(0), 5);
      QCOMPARE(list.at(1), 10);
   }

   void operatorInputStream_listIsEmpty_oneElement()
   {
      QmgObservableList<int> list;

      list << 10;

      QCOMPARE(list.size(), 1);
      QCOMPARE(list.at(0), 10);
   }

   void beforeAddForAppend_listIsEmpty_handlerIsCalledBeforeListIsIncreased()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.beforeAdd() += [&handlerHasBeenCalled, &list](int index, const int &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value, 10);
         QCOMPARE(list.isEmpty(), true);
      };

      list.append(10);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterAddForAppend_listIsEmpty_handlerIsCalledAfterListHasBeenIncreased()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterAdd() += [&handlerHasBeenCalled, &list](int index, const int &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value, 10);
         QCOMPARE(list.isEmpty(), false);
      };

      list.append(10);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void beforeAddForInsert_listIsEmpty_handlerIsCalledBeforeListIsIncreased()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.beforeAdd() += [&handlerHasBeenCalled, &list](int index, const int &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(index, 0);
         QCOMPARE(value, 10);
         QCOMPARE(list.isEmpty(), true);
      };

      list.insert(0, 10);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterAddForInsert_listIsEmpty_handlerIsCalledAfterListHasBeenIncreased()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterAdd() += [&handlerHasBeenCalled, &list](int index, const int &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(index, 0);
         QCOMPARE(value, 10);
         QCOMPARE(list.isEmpty(), false);
      };

      list.insert(0, 10);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void beforeClear_listHasOneElement_handlerIsCalledBeforeListIsCleared()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.beforeClear() += [&handlerHasBeenCalled, &list]() {
         handlerHasBeenCalled = true;
         QCOMPARE(list.isEmpty(), false);
      };

      list.clear();

      QCOMPARE(list.isEmpty(), true);
      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterClear_listHasOneElement_handlerIsCalledAfterListIsCleared()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.afterClear() += [&handlerHasBeenCalled, &list]() {
         handlerHasBeenCalled = true;
         QCOMPARE(list.isEmpty(), true);
      };

      list.clear();

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void beforeRemove_listHasOneElement_handlerIsCalledBeforeListIsDecreased()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.beforeRemove() += [&handlerHasBeenCalled, &list](int index, const int &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value, 10);
         QCOMPARE(list.isEmpty(), false);
      };

      list.removeAt(0);

      QCOMPARE(list.isEmpty(), true);
      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterRemove_listHasOneElement_handlerIsCalledAfterListIsDecreased()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.afterRemove() += [&handlerHasBeenCalled, &list](int index, const int &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value, 10);
         QCOMPARE(list.isEmpty(), true);
      };

      list.removeAt(0);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void beforeUpdate_listHasOneElement_handlerIsCalledBeforeListIsUpdated()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.beforeUpdate() += [&handlerHasBeenCalled, &list](int index, const int &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value, 15);
      };

      list.update(0, 15);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterUpdate_listHasOneElement_handlerIsCalledAfterListIsUpdated()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.afterUpdate() += [&handlerHasBeenCalled, &list](int index, const int &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value, 15);
      };

      list.update(0, 15);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void beforeAddBatch_listIsEmpty_handlerIsCalledBeforeListIsIncreased()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.beforeAddBatch() += [&handlerHasBeenCalled, &list](int index, const QList<int> &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value.at(0), 10);
         QCOMPARE(value.at(1), 15);
         QCOMPARE(list.isEmpty(), true);
      };

      list.append(QList<int>() << 10 << 15);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterAddBatch_listIsEmpty_handlerIsCalledAfterListIsIncreased()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterAddBatch() += [&handlerHasBeenCalled, &list](int index, const QList<int> &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value.at(0), 10);
         QCOMPARE(value.at(1), 15);
         QCOMPARE(list.isEmpty(), false);
      };

      list.append(QList<int>() << 10 << 15);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void beforeAddBatchForStdVector_listIsEmpty_handlerIsCalledBeforeListIsIncreased()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.beforeAddBatch() += [&handlerHasBeenCalled, &list](int index, const QList<int> &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value.at(0), 10);
         QCOMPARE(value.at(1), 15);
         QCOMPARE(list.isEmpty(), true);
      };

      std::vector<int> tmp;
      tmp.push_back(10);
      tmp.push_back(15);

      list.append(tmp);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterAddBatchForStdVector_listIsEmpty_handlerIsCalledAfterListIsIncreased()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterAddBatch() += [&handlerHasBeenCalled, &list](int index, const QList<int> &value) {
         handlerHasBeenCalled = true;
         QCOMPARE(value.at(0), 10);
         QCOMPARE(value.at(1), 15);
         QCOMPARE(list.isEmpty(), false);
      };

      std::vector<int> tmp;
      tmp.push_back(10);
      tmp.push_back(15);

      list.append(tmp);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterChangeForAppend_listIsEmpty_handlerIsCalledAfterListHasChanged()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterChange() += [&handlerHasBeenCalled]() {
         handlerHasBeenCalled = true;
      };

      list.append(10);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterChangeForAppendBatch_listIsEmpty_handlerIsCalledAfterListHasChanged()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterChange() += [&handlerHasBeenCalled]() {
         handlerHasBeenCalled = true;
      };

      list.append(QList<int>() << 10 << 15);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterChangeForAppendBatchStdVector_listIsEmpty_handlerIsCalledAfterListHasChanged()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterChange() += [&handlerHasBeenCalled]() {
         handlerHasBeenCalled = true;
      };

      std::vector<int> tmp;
      tmp.push_back(10);
      tmp.push_back(15);

      list.append(tmp);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterChangeForInsert_listIsEmpty_handlerIsCalledAfterListHasChanged()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterChange() += [&handlerHasBeenCalled]() {
         handlerHasBeenCalled = true;
      };

      list.insert(0, 10);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterChangeForRemove_listHasOneElement_handlerIsCalledAfterListHasChanged()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.afterChange() += [&handlerHasBeenCalled]() {
         handlerHasBeenCalled = true;
      };

      list.removeAt(0);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterChangeForUpdate_listHasOneElement_handlerIsCalledAfterListHasChanged()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.afterChange() += [&handlerHasBeenCalled]() {
         handlerHasBeenCalled = true;
      };

      list.update(0, 15);

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterChangeForClear_listHasOneElement_handlerIsCalledAfterListHasChanged()
   {
      QmgObservableList<int> list;
      list.append(10);

      bool handlerHasBeenCalled = false;
      list.afterChange() += [&handlerHasBeenCalled]() {
         handlerHasBeenCalled = true;
      };

      list.clear();

      QCOMPARE(handlerHasBeenCalled, true);
   }

   void afterChangeForClear_listHasNoElement_handlerIsNotCalledAfterListHasChanged()
   {
      QmgObservableList<int> list;

      bool handlerHasBeenCalled = false;
      list.afterChange() += [&handlerHasBeenCalled]() {
         handlerHasBeenCalled = true;
      };

      list.clear();

      QCOMPARE(handlerHasBeenCalled, false);
   }
};

QTEST_APPLESS_MAIN(QmgObservableListTest)

#include "QmgObservableListTest.moc"
