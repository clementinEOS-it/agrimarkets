#include <agrimarkets.hpp>

#include <eosio/eosio.hpp>
#include <eosio/time.hpp>
#include <eosio/system.hpp>
#include <eosio/crypto.hpp>

using namespace std;
using namespace eosio;

ACTION agrimarkets::post( string               date_at,         // date
                        checksum256          id_hash,          // id
                        string               source,          // info origing data
                        string               category,        // about price 
                        string               type,          // Market type
                        string               city,         // market city
                        string               product,         // product
                        string               price,           // price 
                        float                price_num,       // numeric price
                        string               condition) {
   
   require_auth(get_self());
  
  // Init the _message table
  markets_t _m(get_self(), get_self().value);

  // -----------------------------------------
  // find element by hash key

  auto i_byhash = _m.get_index<"byhash"_n>();
  const auto i = i_byhash.find(id_hash); 

  if ( i == i_byhash.end() ) {

    _m.emplace(get_self(), [&](auto& item) {
      item.from = get_self();
      item.id = _m.available_primary_key();
      item.date_at = date_at;
      item.id_hash = id_hash;   
      item.source = source;                 
      item.category = category;   
      item.type = type; 
      item.city = city;                
      item.product = product;                 
      item.price = price;           
      item.price_num = price_num; 
      item.condition = condition; 
    });
  
  } else {

    i_byhash.modify(i, get_self(), [&]( auto& item ) {
      item.date_at = date_at;
      item.source = source;                 
      item.category = category;   
      item.type = type; 
      item.city = city;                
      item.product = product;                 
      item.price = price;           
      item.price_num = price_num;  
      item.condition = condition;
    });
  }
};

// Delete all records in covid table
ACTION agrimarkets::clear(uint64_t id) {

  require_auth(get_self());

  markets_t _m(get_self(), get_self().value);
  const auto i = _m.find(id); 

  if ( i == _m.end() ) {
    auto item = _m.begin();
    while (item != _m.end()) {
      item = _m.erase(item);
    }
  } else {
    _m.erase(i);
  }
}

EOSIO_DISPATCH(agrimarkets, 
               (post)
               (clear));

