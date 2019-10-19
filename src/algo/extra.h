#ifndef BITCOIN_ALGO_EXTRA_H
#define BITCOIN_ALGO_EXTRA_H

uint32_t be32dec(uint32_t *pp);
uint32_t be32enc(uint32_t *pp, uint32_t x);
uint32_t le32dec(uint32_t *pp);
uint32_t le32enc(uint32_t *pp, uint32_t x);

#endif // BITCOIN_ALGO_EXTRA_H
