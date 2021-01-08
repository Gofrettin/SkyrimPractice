#pragma once
#include <array>
#include <algorithm>

template< typename T, size_t T_Size >
class Vector {
public:
	using Arr_t = std::array< T, T_Size >;
	using Vec_t = Vector< T, T_Size >;

	Vector(void) {
		static_assert(std::is_arithmetic< T >::value, "Type T has to be arithmetic");
		static_assert(T_Size >= 2, "Vector does require a min. dimension of 2");
		fill(static_cast<T>(0));
	}

	explicit Vector(const Arr_t& arr) : m_Data(arr) {
		static_assert(std::is_arithmetic< T >::value, "Type T has to be arithmetic");
		static_assert(T_Size >= 2, "Vector does require a min. dimension of 2");
	}

	template < typename... Args >
	Vector(Args... args) : m_Data{ static_cast<T>(std::forward< Args >(args))... } {
		static_assert(std::is_arithmetic< T >::value, "Type T has to be arithmetic");
		static_assert(T_Size >= 2, "Vector does require a min. dimension of 2");
	}

	T& operator () (const size_t index) {
		return at(index);
	}

	const T& operator () (const size_t index) const {
		return at(index);
	}

	T& operator [] (const size_t index) {
		return at(index);
	}

	const T& operator [] (const size_t index) const {
		return at(index);
	}

	/**
	* @brief      Returns a value by index.
	*
	* @Param[in]  index  The index
	*
	* @returN     The value.
	*/
	T& at(const size_t index) {
		return m_Data.at(index >= T_Size ? T_Size - 1 : index);
	}

	/**
	* @brief      Returns a value by index.
	*
	* @Param[in]  index  The index
	*
	* @returN     The value.
	*/
	const T& at(const size_t index) const {
		return m_Data.at(index >= T_Size ? T_Size - 1 : index);
	}

	Vector& operator = (const Vec_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) = other(i);
		}
		return *this;
	}

	Vector& operator = (const Arr_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) = other.at(i);
		}
		return *this;
	}

	Vector& operator = (const T other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) = other;
		}
		return *this;
	}

	Vector operator + (const Vec_t& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) + other(i);
		}
		return buf;
	}

	Vector operator + (const Arr_t& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) + other.at(i);
		}
		return buf;
	}

	Vector operator + (const T& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) + other;
		}
		return buf;
	}

	Vector& operator += (const Vec_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) += other(i);
		}
		return *this;
	}

	Vector& operator += (const Arr_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) += other.at(i);
		}
		return *this;
	}

	Vector& operator += (const T& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) += other;
		}
		return *this;
	}

	Vector operator - (const Vec_t& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) - other(i);
		}
		return buf;
	}

	Vector operator - (const Arr_t& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) - other.at(i);
		}
		return buf;
	}

	Vector operator - (const T& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) - other;
		}
		return buf;
	}

	Vector& operator -= (const Vec_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) -= other(i);
		}
		return *this;
	}

	Vector& operator -= (const Arr_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) -= other.at(i);
		}
		return *this;
	}

	Vector& operator -= (const T& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) -= other;
		}
		return *this;
	}

	Vector operator * (const Vec_t& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) * other(i);
		}
		return buf;
	}

	Vector operator * (const Arr_t& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) * other.at(i);
		}
		return buf;
	}

	Vector operator * (const T& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) * other;
		}
		return buf;
	}

	Vector& operator *= (const Vec_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) *= other(i);
		}
		return *this;
	}

	Vector& operator *= (const Arr_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) *= other.at(i);
		}
		return *this;
	}

	Vector& operator *= (const T& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) *= other;
		}
		return *this;
	}

	Vector operator / (const Vec_t& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) / other(i);
		}
		return buf;
	}

	Vector operator / (const Arr_t& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) / other.at(i);
		}
		return buf;
	}

	Vector operator / (const T& other) {
		Vec_t buf;
		for (size_t i = 0; i < T_Size; ++i) {
			buf(i) = at(i) / other;
		}
		return buf;
	}

	Vector& operator /= (const Vec_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) /= other(i);
		}
		return *this;
	}

	Vector& operator /= (const Arr_t& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) /= other.at(i);
		}
		return *this;
	}

	Vector& operator /= (const T& other) {
		for (size_t i = 0; i < T_Size; ++i) {
			at(i) /= other;
		}
		return *this;
	}

	/**
	* @brief      Determines if is equal to another vector.
	*
	* @Param[in]  other  The other
	*
	* @returN     True if equal, False otherwise.
	*/
	bool operator == (const Vec_t& other) const {
		for (size_t i = 0; i < T_Size; ++i) {
			if (at(i) != other(i)) {
				return false;
			}
		}
		return true;
	}

	/**
	* @brief      Determines if is equal to another array of values.
	*
	* @Param[in]  other  The other
	*
	* @returN     True if equal, False otherwise.
	*/
	bool operator == (const Arr_t& other) const {
		for (size_t i = 0; i < T_Size; ++i) {
			if (at(i) != other.at(i)) {
				return false;
			}
		}
		return true;
	}

	/**
	* @brief      Determines if is equal to another value.
	*
	* @Param[in]  other  The other
	*
	* @returN     True if equal, False otherwise.
	*/
	bool operator == (const T& other) const {
		for (size_t i = 0; i < T_Size; ++i) {
			if (at(i) != other) {
				return false;
			}
		}
		return true;
	}

	/**
	* @brief      Determines if is not equal to another vector.
	*
	* @Param[in]  other  The other
	*
	* @returN     True if not equal, False otherwise.
	*/
	bool operator != (const Vec_t& other) const {
		return !(*this == other);
	}

	/**
	* @brief      Determines if is not equal to an array of values.
	*
	* @Param[in]  other  The other
	*
	* @returN     True if not equal, False otherwise.
	*/
	bool operator != (const Arr_t& other) const {
		return !(*this == other);
	}

	/**
	* @brief      Determines if is not equal to a value.
	*
	* @Param[in]  other  The other
	*
	* @returN     True if not equal, False otherwise.
	*/
	bool operator != (const T& other) const {
		return !(*this == other);
	}

	/**
	* @brief      Returns the size.
	*
	* @returN     The size.
	*/
	static constexpr size_t size(void) {
		return T_Size;
	}

	/**
	* @brief      Returns the array values.
	*
	* @returN     The array values.
	*/
	Arr_t values(void) const {
		return m_Data;
	}

	/**
	* @brief      Returns the array values as pointer.
	*
	* @returN     The array values data.
	*/
	const Arr_t* data(void) const {
		return &m_Data;
	}

	/**
	* @brief      Determines if empty.
	*
	* @returN     True if empty, False otherwise.
	*/
	bool empty(void) const {
		return std::all_of(m_Data.begin(), m_Data.end(), [](T value) {
			return value == static_cast<T>(0);
			});
	}

	/**
	* @brief      Gets the distance.
	*
	* @Param[in]  other  The other
	*
	* @returN     The distance.
	*/
	T get_distance(const Vec_t& other) const {
		return (other - (*this)).get_length();
	}

	/**
	* @brief      Gets the distance.
	*
	* @Param[in]  other  The other
	*
	* @returN     The distance.
	*/
	T get_distance(Vec_t& other) const {
		return (other - (*this)).get_length();
	}

	/**
	* @brief      Gets the length.
	*
	* @returN     The length.
	*/
	T get_length(void) const {
		return sqrt(get_length_sqr());
	}

	/**
	* @brief      Gets the length sqr.
	*
	* @returN     The length sqr.
	*/
	T get_length_sqr(void) const {
		T buf = static_cast<T>(0);
		for (const auto& i : m_Data) {
			buf += (i * i);
		}
		return buf;
	}

	/**
	* @brief      Fill out each value.
	*
	* @Param[in]  value  The value
	*/
	void fill(const T value) {
		m_Data.fill(value);
	}

	/**
	* @brief      Normalize the vector.
	*/
	void normalize(void) {
		(*this) /= get_length();
	}

	/**
	* @brief      Gets the cross product.
	*
	* @Param[in]  other                    The other
	* @Param[in]  normalize_cross_product  The normalize cross product
	*
	* @returN     The cross product.
	*/
	Vec_t cross_product(const Vec_t& other, const bool normalize_cross_product = false) const {
		static_assert(T_Size == 3, "The cross product can only be calculated for 3 dimensional vectors");
		auto vec = Vec_t(
			at(1) * other(2) - at(2) * other(1),
			at(2) * other(0) - at(0) * other(2),
			at(0) * other(1) - at(1) * other(0)
		);

		if (normalize_cross_product) {
			vec.normalize();
		}
		return vec;
	}

	/**
	* @brief      Gets the inversed.
	*
	* @returN     The inversed.
	*/
	Vec_t inversed(void) const {
		auto vec = *this;
		const auto one = static_cast<T>(1);
		for (auto& i : vec) {
			i = one / i;
		}
		return vec;
	}

	/**
	* @brief      Gets the normalized.
	*
	* @returN     The normalized.
	*/
	Vec_t normalized(void) const {
		auto vec = *this;
		vec.normalize();
		return vec;
	}

	/**
	* @brief      Returns the dot product.
	*
	* @Param[in]  other    The other
	*
	* @tparam     T2       The other data type
	* @tparam     T2_Size  The other dimension
	*
	* @returN     The dot product.
	*/
	template< typename T2, size_t T2_Size >
	T dot_product(const Vector< T2, T2_Size >& other) const {
		auto dot = static_cast<T>(0);
		for (size_t i = 0; i < (T_Size < T2_Size ? T_Size : T2_Size); ++i) {
			dot += at(i) * other(i);
		}

		return dot;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec_t& v) {
		for (size_t i = 0; i < T_Size; ++i) {
			os << v(i);
			if (i + 1 != T_Size) {
				os << " - ";
			}
		}
		return os;
	}

private:
	Arr_t m_Data;
};

using Vector4 = Vector< float, 4 >;
using Vector3 = Vector< float, 3 >;
using Vector2 = Vector< float, 2 >;