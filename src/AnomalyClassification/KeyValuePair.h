#ifndef KeyValuePair_H
#define KeyValuePair_H

template <class KEY, class VALUE >
class KeyValuePair 
{
public:
	KEY key;
	VALUE value;

	KeyValuePair(KEY key, VALUE value)
	{
		this->key = key;
		this->value = value;
	}

	bool operator==(KeyValuePair<KEY, VALUE> a)
	{
		return this->key == a.key && this->value == a.value;
	}

	bool operator<(KeyValuePair<KEY, VALUE> a)
	{
		return this->key < a.key;
	}
};

#endif