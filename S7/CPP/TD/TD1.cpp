#include <iostream>
#include <assert.h>
using namespace std;

class div_by_zero { };

class complex {
public:

	//complex(): _real(0), _imag(0) { }
	//complex(double a, double b): _real(a), _imag(b) { }

	constexpr complex(double a = 0, double b = 0): _real(a), _imag(b) { }

	/*complex(double a = 0, double b = 0) {
		_real = a;
		_imag = b;
	}*/

	complex operator+(const complex& c) const {
		return complex(_real + c._real, _imag + c._imag);
	}

	complex operator-(const complex& c) const {
		return complex(_real - c._real, _imag - c._imag);
	}

	complex operator*(const complex& c) const {
		return complex(
			_real * c._real - _imag * c._imag,
			_real * c._imag + c._real * _imag
		);
	}

	complex operator/(double x) const {
		if(x == 0)
			throw div_by_zero();
		else
			return complex(_real / x, _imag / x);
	}

	complex operator/(const complex& z) const {
		return *this * ~z / (z * ~z).real();
	}
	
	complex operator~() const {
		return complex(_real, -_imag);
	}

	inline const double& real() const { return _real; }
	inline double& real() { return _real; }
	inline double imag() const { return _imag; }

	static const complex zero, i, one;

private:
	double _real, _imag;
};

const complex
	complex::zero(0, 0),
	complex::i(0, 1),
	complex::one(1, 0);

// démarrage ====> complex::ceomplex(0,0)
//		zero.complex(0,0)
//		i.complex(0,1)
//		one.complex(1,0)

//	constexpre
// 	compilation ====>
//		zero.complex(0,0)
//		i.complex(0,1)
//		one.complex(1,0)
//
//	démarrage du programme ====>

/*complex operator+(const complex& z, const complex& c) {
	return complex(z._real + c._real, z._imag + c._imag);
}*/

// << c'est le printf du c++
ostream& operator<<(ostream& out, complex z){
	out << z.real() << " + " << z.imag() << "i";
	return out;
}

istream& operator>>(istream& in, complex& z){
	double r,i;
	in >> r >> i;
	z=complex(r,i);
	return in;
}


class CVector {
public:
	CVector(int C)
	: _t(new complex[C]), _N(0), _C(C) 
	{}
	~CVector(){
		delete [] _t;
	}

	inline const complex& operator[](int i) const {
		assert(0<=i && i<_N);
		return _t[i];
	}

	inline complex& operator[](int i) {
		assert(0<=i && i<_N);
		return _t[i];
	}

	void push_back(const complex& c) {
		assert(_N < _C);	//permet d'être sûr que le nombre d'éléments est inférieur à la capacité du tableau _t
		_t[_N++]=c;
		//_N++;
	}

	inline int N() const { return _N; }	

	class iterator {
		friend class CVector;
	public:
		
		iterator(const CVector& vec, int ii=0): v(vec), i(ii) {}

		inline bool operator==(const iterator& it) const {
			return &v == &it.v && i == it.i;
		}

		inline bool operator!=(const iterator& it) const {
			return !operator==(it);
		}
		
		inline complex operator*() const {
			return v[i];
		}
		
		inline iterator& operator++() { // pre-incrémentation
			++i; return *this;
		}
		
	private:
		
		const CVector& v;
		int i;
	};

	inline iterator begin() const { return iterator(*this); }
	inline iterator end() const { return iterator(*this,_N); }

	void erase(const iterator& it) {
		for(int i=it.i +1;i<_N;i++)
			_t[i-1]=_t[i];
		_N--;
	}

private:
	complex *_t;
	int _N, _C;	// N nombre d'éléments dans le tableau et C capacité du tableau
};

ostream& operator<<(ostream& out, const CVector& v){
	for(int i=0;i<v.N();i++){
		out << v[i] << endl;
		return out;
	}
}

int main() {
	auto c1 = complex();
	complex c2;
	complex c3(5);		// 5 + 0i
	complex c4(3, 5);	// 3 + 5i

	auto c5 = c3 + c4;
	cout << c5.real() << " + " << c5.imag() << "i" << endl;
	c5.real() = 3;
	const complex c6;
	//c6.real() = 3;
	/*
	try {
		auto c7 = c5 / complex::zero;
	}
	catch(div_by_zero) {
		cerr << "erreur !" << endl;
	}
	*/

	cout << c5 << endl;
	cin >> c5;

	const CVector v(10);	
	cout << v[3];

	CVector v2(10);
	v2[3] = 0;
	cout << v2[3];

	v2.push_back(complex(1,1));

	cout << v2;

	for(auto i = v.begin(); i!=v.end(); ++i)
		cout << *i << endl;

	for(const auto i:v)
		cout << i << endl;
}
