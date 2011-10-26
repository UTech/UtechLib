#ifndef U2LIST_H
#define U2LIST_H

#include <QObject>
#include <QList>
	
template <class Key, class T>
class U2List
{
  public:
	U2List();
	
	int capacity();
	void clear();
	void count();
	bool empty();
	void insert(const Key & key, const T & value);
	bool isEmpty();
	const Key key(const T & value) const;
	const Key key(const T & value, const Key & defaultKey) const;
	const Key keyAt(int pos) const;
	void replaceKeyAt(int pos, const Key & key);
	int	remove(const Key & key);
	int	size() const;
	const T	value(const Key & key) const;
	const T	value(const Key & key, const T & defaultValue) const;
	const T valueAt(int pos) const;
	void replaceValueAt(int pos, const T & value);
  private:
	QList<Key> keyList;
	QList<T> valueList;
};

template <class Key, class T>
U2List<Key, T>::U2List()
{

}

template <class Key, class T>
int U2List<Key, T>::capacity()
{
	return keyList.size();
}

template <class Key, class T>
void U2List<Key, T>::clear()
{
	keyList.clear();
	valueList.clear();
}

template <class Key, class T>
void U2List<Key, T>::count()
{
	return keyList.size();
}

template <class Key, class T>
bool U2List<Key, T>::empty()
{
	if (keyList.empty())
		return true;
	return false;
}

template <class Key, class T>
void U2List<Key, T>::insert(const Key & key, const T & value)
{
	keyList.append(key);
	valueList.append(value);
}

template <class Key, class T>
bool U2List<Key, T>::isEmpty()
{
	if (keyList.empty())
		return true;
	return false;
}

template <class Key, class T>
const Key U2List<Key, T>::key(const T & value) const
{
	if (valueList.contains(value)){
		return keyList.at(valueList.indexOf(value));
	}
	else
		return Key();
}

template <class Key, class T>
const Key U2List<Key, T>::key(const T & value, const Key & defaultKey) const
{
	if (valueList.contains(value)){
		return keyList.at(valueList.indexOf(value));
	}
	else
		return defaultKey;
}

template <class Key, class T>
const Key U2List<Key, T>::keyAt(int pos) const
{
	return keyList.at(pos);
}

template <class Key, class T>
void U2List<Key, T>::replaceKeyAt(int pos, const Key & key )
{
	keyList.replace(pos, key);
}

template <class Key, class T>
int	U2List<Key, T>::remove(const Key & key)
{
	int count = 0;
	for (int i = 0; i < keyList.size(); ++i) {
	    if ( keyList.at(i) == key ) {
		    keyList.removeAt(i);
			valueList.removeAt(i);
			--i;
			++count;
		}
	}
	return count;
}

template <class Key, class T>
int	U2List<Key, T>::size() const
{
	return keyList.size();
}

template <class Key, class T>
const T	U2List<Key, T>::value(const Key & key) const
{
	if (keyList.contains(key)){
		return valueList.at(keyList.indexOf(key));
	}
	else
		return T();
}

template <class Key, class T>
const T	U2List<Key, T>::value(const Key & key, const T & defaultValue) const
{
	if (keyList.contains(key)){
		return valueList.at(keyList.indexOf(key));
	}
	else
		return defaultValue;
}

template <class Key, class T>
const T U2List<Key, T>::valueAt(int pos) const
{
	return valueList.at(pos);
}

template <class Key, class T>
void U2List<Key, T>::replaceValueAt(int pos, const T & value)
{
	valueList.replace(pos, value);
}

typedef U2List<int, QString> UIntStringList;

#endif
