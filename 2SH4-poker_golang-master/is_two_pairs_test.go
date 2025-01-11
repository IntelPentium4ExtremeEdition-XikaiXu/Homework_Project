package poker_test

import (
	"testing"

	"github.com/fakovacic/poker"
)

func TestIsTwoPairs(t *testing.T) {
	cases := []struct {
		it             string
		cards          []*poker.Card
		expectedResult bool
	}{
		{
			it: "ok, 4 cards",
			cards: []*poker.Card{
				{
					Rank: poker.Ace,
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
			},
			expectedResult: true,
		},
		{
			it: "ok, 5 cards",
			cards: []*poker.Card{
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Queen,
				},
				{
					Rank: poker.King,
				},
				{
					Rank: poker.King,
				},
			},
			expectedResult: true,
		},
		{
			it: "not ok, 4 cards",
			cards: []*poker.Card{
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.King,
				},
				{
					Rank: poker.Queen,
				},
				{
					Rank: poker.Jack,
				},
			},
			expectedResult: false,
		},
		{
			it: "not ok, 4 cards",
			cards: []*poker.Card{
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Queen,
				},
				{
					Rank: poker.Jack,
				},
			},
			expectedResult: false,
		},
		{
			it: "not ok, 4 cards",
			cards: []*poker.Card{
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Jack,
				},
			},
			expectedResult: false,
		},
		{
			it: "not ok, 5 cards",
			cards: []*poker.Card{
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Queen,
				},
				{
					Rank: poker.Jack,
				},
				{
					Rank: poker.King,
				},
			},
			expectedResult: false,
		},
		{
			it: "not ok, 5 cards",
			cards: []*poker.Card{
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Jack,
				},
				{
					Rank: poker.King,
				},
			},
			expectedResult: false,
		},
		{
			it: "not ok, 2 cards",
			cards: []*poker.Card{
				{
					Rank: poker.Ace,
				},
				{
					Rank: poker.Ace,
				},
			},
			expectedResult: false,
		},
	}

	for _, tc := range cases {
		t.Run(tc.it, func(t *testing.T) {
			res := poker.IsTwoPairs(tc.cards)
			if tc.expectedResult != res {
				t.Errorf("expected: '%v' got: '%v'", tc.expectedResult, res)
			}
		})
	}
}
