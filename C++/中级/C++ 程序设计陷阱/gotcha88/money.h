#ifndef MONEY_H
#define MONEY_H

enum Currency { CAD, DM, USD, Yen };

class Curve {
  public:
	Curve( Currency )
		{}
	double convert( Currency, Currency, double amt ) const
		{ return amt; }
};

template <Currency currency>
class Money {
  public:
    Money( double amt );
    template <Currency otherCurrency>
        Money( const Money<otherCurrency> & );
    template <Currency otherCurrency>
        Money &operator =( const Money<otherCurrency> & );
    ~Money();
    double get_amount() const
    	{ return amt_; }
    //...
  private:
    Curve *myCurve_;
	double amt_;
};


template <Currency currency>
Money<currency>::Money( double amt )
	: myCurve_( new Curve(currency) ), amt_(amt) {}

template <Currency currency>
Money<currency>::~Money()
	{ delete myCurve_; }

template <Currency currency>
template <Currency otherCurrency>
Money<currency>::Money( const Money<otherCurrency> &that )
	: myCurve_( new Curve(currency) ), amt_(myCurve_->convert(currency,otherCurrency,that.get_amount())) {}

template <Currency currency>
template <Currency otherCurrency>
Money<currency> &Money<currency>::operator =( const Money<otherCurrency> &rhs ) {
	amt_ = myCurve_->convert( currency, otherCurrency, rhs.get_amount() );
	return *this;
}

#endif
