#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>
#include <eosio/time.hpp>
#include <eosio/system.hpp>

using namespace eosio;
using namespace std;

CONTRACT agrimarkets : public contract {
   public:
      using contract::contract;

      ACTION post( string               date_at,         // date
                   checksum256          id_hash,          // id
                   string               source,          // info origing data
                   string               category,        // about price 
                   string               type,          // Market type
                   string               city,         // market city
                   string               product,         // product
                   string               price,           // price 
                   float                price_num,       // numeric price
                   string               condition);
      ACTION clear(uint64_t id);
   
   private:
      TABLE market {
      name                 from;
      uint64_t             id;           
      string               date_at;         // date
      checksum256          id_hash;         // id
      string               source;          // info origing data
      string               category;        // about price 
      string               type;          // Market city
      string               city;
      string               product;         // product
      string               price;           // price 
      float                price_num;       // numeric price
      string               condition;   
      
      uint64_t primary_key() const { 
        return id; 
      }

      checksum256 by_hash() const { 
        return id_hash; 
      }

    };

    typedef multi_index<
      "markets"_n,
      market,
      indexed_by<"byhash"_n, const_mem_fun<market, checksum256, &market::by_hash>>>
      markets_t;
};


/*

categoria: m.category,
            mercato: m.type,
            piazza: '',
            data: '',
            prodotto: '',
            prezzo: '',
            prezzo_num: 0,
            var: '',
            condizioni: ''


*/