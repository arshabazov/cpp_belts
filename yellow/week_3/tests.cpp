#include "tests.h"

void testAddSynonyms() {
	{
		Synonyms empty;
		addSynonyms(empty, "a", "b");
		const Synonyms expected = {
			{"a", {"b"}},
			{"b", {"a"}}
		};
		assertEqual(empty, expected, "adding synonyms a and b to an empty set");
	}
	{
		Synonyms synonyms = {
			{"a", {"b"}},
			{"b", {"a", "c"}},
			{"c", {"b"}}
		};
		addSynonyms(synonyms, "a", "c");
		const Synonyms expected = {
			{"a", {"b", "c"}},
			{"b", {"a", "c"}},
			{"c", {"b", "a"}}
		};
		assertEqual(synonyms, expected, "adding synonyms a and c to a set");
	}
}

void testGetSynonymsCount() {
	{
		Synonyms empty;
		assertEqual(getSynonymsCount(empty, "a"), 0, "Count synonyms for an empty set");
	}
	{
		Synonyms synonyms = {
			{"a", {"b", "c"}},
			{"b", {"a"}},
			{"c", {"a"}}
		};
		assertEqual(getSynonymsCount(synonyms, "a"), 2, "Count 2 synonyms for a");
		assertEqual(getSynonymsCount(synonyms, "b"), 1, "Count 1 synonym for b");
		assertEqual(getSynonymsCount(synonyms, "z"), 0, "Count 0 synonyms for z");
	}
}

void testAreSynonyms() {
	{
		Synonyms empty;
		Assert(!areSynonyms(empty, "a" ,"b"), "Are a b synonyms in an empty set");
		Assert(!areSynonyms(empty, "b", "a"), "Are b a synonyms in an empty set");
	}
	{
		Synonyms synonyms = {
			{"a", {"b", "c"}},
			{"b", {"a"}},
			{"c", {"a"}}
		};
		Assert(areSynonyms(synonyms, "a", "b"), "Are a and b synonyms");
		Assert(areSynonyms(synonyms, "b", "a"), "Are b and a synonyms");
		Assert(areSynonyms(synonyms, "a", "c"), "Are a and c synonyms");
		Assert(areSynonyms(synonyms, "c", "a"), "Are c and a synonyms");
		Assert(!areSynonyms(synonyms, "b", "c"), "Are b and c synonyms");
		Assert(!areSynonyms(synonyms, "c", "b"), "Are c and b synonyms");
	}
}

void testAll() {
	TestRunner tester;
	tester.runTest(testAddSynonyms, "testAddSynonyms");
	tester.runTest(testGetSynonymsCount, "testGetSynonymsCount");
	tester.runTest(testAreSynonyms, "testAreSynonyms");
}