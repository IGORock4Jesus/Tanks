#pragma once

#define PROPERTY(type, name) \
private:\
	type _##name;\
public:\
	type Get##name() const { return _##name; }\
	void Set##name(type name) { _##name = name; }\
private:


#define PROPERTY_GET(type, name) \
private:\
	type _##name;\
public:\
	type Get##name() const { return _##name; }\
private:


#define PROPERTY_CUSTOM_SET(type, name, setter) \
private:\
	type _##name;\
public:\
	type Get##name() const { return _##name; }\
	void Set##name(type name) { _##name = name; setter(name); }\
private:
