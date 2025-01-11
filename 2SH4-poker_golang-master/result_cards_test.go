package poker_test

import (
	"testing"

	"github.com/fakovacic/poker"
)

func TestResultCards(t *testing.T) {
	cases := []struct {
		it             string
		cards          []*poker.Card
		result         poker.Result
		expectedResult []int64
	}{
		{
			it: "high-card",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Ten,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Queen,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Ace,
				},
			},
			result: poker.HighCard,
			expectedResult: []int64{
				4,
			},
		},
		{
			it: "high-card - 1 card",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Ace,
				},
			},
			result: poker.HighCard,
			expectedResult: []int64{
				0,
			},
		},
		{
			it: "pair",
			cards: []*poker.Card{
				{
					Suite: poker.Hearts,
					Rank:  poker.Ace,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Nine,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Jack,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Jack,
				},
			},
			result: poker.Pair,
			expectedResult: []int64{
				3, 4,
			},
		},
		{
			it: "pair - 2 card",
			cards: []*poker.Card{
				{
					Suite: poker.Diamonds,
					Rank:  poker.Jack,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Jack,
				},
			},
			result: poker.Pair,
			expectedResult: []int64{
				0,
			},
		},
		{
			it: "pair",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Ten,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Ace,
				},
			},
			result: poker.Pair,
			expectedResult: []int64{
				2, 3,
			},
		},
		{
			it: "pair",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Ace,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Ace,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Queen,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Two,
				},
			},
			result: poker.Pair,
			expectedResult: []int64{
				0, 1,
			},
		},
		{
			it: "two-pairs",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Ace,
				},
			},
			result: poker.TwoPairs,
			expectedResult: []int64{
				0, 1, 2, 3,
			},
		},
		{
			it: "two-pairs - 4 cards",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Two,
				},
			},
			result: poker.TwoPairs,
			expectedResult: []int64{
				0, 1, 2, 3,
			},
		},
		{
			it: "three-of-a-kind",
			cards: []*poker.Card{
				{
					Suite: poker.Hearts,
					Rank:  poker.Three,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Three,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.King,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Three,
				},
			},
			result: poker.ThreeOfAKind,
			expectedResult: []int64{
				0, 2, 4,
			},
		},
		{
			it: "three-of-a-kind - 3 cards",
			cards: []*poker.Card{
				{
					Suite: poker.Hearts,
					Rank:  poker.Three,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Three,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Three,
				},
			},
			result: poker.ThreeOfAKind,
			expectedResult: []int64{
				0, 1, 2,
			},
		},
		{
			it: "three-of-a-kind",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Ace,
				},
			},
			result: poker.ThreeOfAKind,
			expectedResult: []int64{
				0, 1, 2,
			},
		},
		{
			it: "straight",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Six,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Five,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Three,
				},
			},
			result: poker.Straight,
			expectedResult: []int64{
				0, 1, 2, 3, 4,
			},
		},
		{
			it: "straight - high cards",
			cards: []*poker.Card{
				{
					Suite: poker.Spades,
					Rank:  poker.Nine,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Ten,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Jack,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Queen,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.King,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Ace,
				},
			},
			result: poker.Straight,
			expectedResult: []int64{
				1, 2, 3, 4, 5,
			},
		},
		{
			it: "flush",
			cards: []*poker.Card{
				{
					Suite: poker.Diamonds,
					Rank:  poker.Queen,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Five,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Three,
				},
			},
			result: poker.Flush,
			expectedResult: []int64{
				0, 1, 2, 3, 4,
			},
		},
		{
			it: "full-house",
			cards: []*poker.Card{
				{
					Suite: poker.Diamonds,
					Rank:  poker.Queen,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Queen,
				},
				{
					Suite: poker.Clubs,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Four,
				},
			},
			result: poker.FullHouse,
			expectedResult: []int64{
				0, 1, 2, 3, 4,
			},
		},
		{
			it: "four-of-a-kind",
			cards: []*poker.Card{
				{
					Suite: poker.Diamonds,
					Rank:  poker.Queen,
				},
				{
					Suite: poker.Hearts,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Clubs,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Four,
				},
			},
			result: poker.FourOfAKind,
			expectedResult: []int64{
				1, 2, 3, 4,
			},
		},
		{
			it: "four-of-a-kind - 4 cards",
			cards: []*poker.Card{
				{
					Suite: poker.Hearts,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Clubs,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Four,
				},
				{
					Suite: poker.Spades,
					Rank:  poker.Four,
				},
			},
			result: poker.FourOfAKind,
			expectedResult: []int64{
				0, 1, 2, 3,
			},
		},
		{
			it: "straight-flush",
			cards: []*poker.Card{
				{
					Suite: poker.Diamonds,
					Rank:  poker.Five,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Ace,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Two,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Three,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Four,
				},
			},
			result: poker.StraightFlush,
			expectedResult: []int64{
				0, 1, 2, 3, 4,
			},
		},
		{
			it: "royal-flush",
			cards: []*poker.Card{
				{
					Suite: poker.Diamonds,
					Rank:  poker.Ten,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Jack,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Queen,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.King,
				},
				{
					Suite: poker.Diamonds,
					Rank:  poker.Ace,
				},
			},
			result: poker.RoyalFlush,
			expectedResult: []int64{
				0, 1, 2, 3, 4,
			},
		},
	}

	for _, tc := range cases {
		t.Run(tc.it, func(t *testing.T) {
			for i := range tc.expectedResult {
				res := poker.ResultCards(tc.result, tc.cards)
				if tc.expectedResult[i] != res[i] {
					t.Errorf("expected cards %d: '%v' got: '%v'", i, tc.expectedResult[i], res[i])
				}
			}
		})
	}
}

func benchmarkResultCards(result poker.Result, cards []*poker.Card, b *testing.B) {
	for n := 0; n < b.N; n++ {
		poker.ResultCards(result, cards)
	}
}

func BenchmarkResultCardsHighCard(b *testing.B) {
	benchmarkResultCards(poker.HighCard, []*poker.Card{
		{
			Rank: poker.Ace,
		},
		{
			Rank: poker.King,
		},
		{
			Rank: poker.Ace,
		},
		{
			Rank: poker.King,
		},
		{
			Rank: poker.King,
		},
	}, b)
}
func BenchmarkResultCardsPair(b *testing.B) {
	benchmarkResultCards(poker.Pair, []*poker.Card{
		{
			Suite: poker.Spades,
			Rank:  poker.Ten,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Six,
		},
		{
			Suite: poker.Hearts,
			Rank:  poker.Two,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Two,
		},
		{
			Suite: poker.Spades,
			Rank:  poker.Ace,
		},
	}, b)
}
func BenchmarkResultCardsTwoPair(b *testing.B) {
	benchmarkResultCards(poker.TwoPairs, []*poker.Card{
		{
			Suite: poker.Spades,
			Rank:  poker.Six,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Six,
		},
		{
			Suite: poker.Hearts,
			Rank:  poker.Two,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Two,
		},
		{
			Suite: poker.Spades,
			Rank:  poker.Ace,
		},
	}, b)
}

func BenchmarkResultCardsThreeOfAKind(b *testing.B) {
	benchmarkResultCards(poker.ThreeOfAKind, []*poker.Card{
		{
			Suite: poker.Spades,
			Rank:  poker.Six,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Six,
		},
		{
			Suite: poker.Hearts,
			Rank:  poker.Six,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Two,
		},
		{
			Suite: poker.Spades,
			Rank:  poker.Ace,
		},
	}, b)
}

func BenchmarkResultCardsStraight(b *testing.B) {
	benchmarkResultCards(poker.Straight, []*poker.Card{
		{
			Suite: poker.Spades,
			Rank:  poker.Six,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Five,
		},
		{
			Suite: poker.Hearts,
			Rank:  poker.Four,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Two,
		},
		{
			Suite: poker.Spades,
			Rank:  poker.Three,
		},
	}, b)
}

func BenchmarkResultCardsFlush(b *testing.B) {
	benchmarkResultCards(poker.Flush, []*poker.Card{
		{
			Suite: poker.Diamonds,
			Rank:  poker.Queen,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Five,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Four,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Two,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Three,
		},
	}, b)
}

func BenchmarkResultCardsFullHouse(b *testing.B) {
	benchmarkResultCards(poker.FullHouse, []*poker.Card{
		{
			Suite: poker.Diamonds,
			Rank:  poker.Queen,
		},
		{
			Suite: poker.Hearts,
			Rank:  poker.Queen,
		},
		{
			Suite: poker.Clubs,
			Rank:  poker.Four,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Four,
		},
		{
			Suite: poker.Spades,
			Rank:  poker.Four,
		},
	}, b)
}

func BenchmarkResultCardsFourOfAKind(b *testing.B) {
	benchmarkResultCards(poker.FourOfAKind, []*poker.Card{
		{
			Suite: poker.Diamonds,
			Rank:  poker.Queen,
		},
		{
			Suite: poker.Hearts,
			Rank:  poker.Four,
		},
		{
			Suite: poker.Clubs,
			Rank:  poker.Four,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Four,
		},
		{
			Suite: poker.Spades,
			Rank:  poker.Four,
		},
	}, b)
}

func BenchmarkResultCardsStraightFlush(b *testing.B) {
	benchmarkResultCards(poker.StraightFlush, []*poker.Card{
		{
			Suite: poker.Diamonds,
			Rank:  poker.Five,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Ace,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Two,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Three,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Four,
		},
	}, b)
}

func BenchmarkResultCardsRoyalFlush(b *testing.B) {
	benchmarkResultCards(poker.RoyalFlush, []*poker.Card{
		{
			Suite: poker.Diamonds,
			Rank:  poker.Ten,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Jack,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Queen,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.King,
		},
		{
			Suite: poker.Diamonds,
			Rank:  poker.Ace,
		},
	}, b)
}
