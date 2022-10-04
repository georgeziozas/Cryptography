
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

int main(void)
{
    mpz_t p,q,n, d, e, plain_text, chypher_text;

    mpz_init(plain_text);
    mpz_init(chypher_text);

    mpz_init_set_str(p, "12631340487377764331146087425363249956246213670504265365396656530933488746717216354206576950424293615561874161074108862487986499779584893634939629371572551", 10);
    mpz_init_set_str(q, "11201044270905991766462199176480586626956240101904553806575932808610272254907364992951088858764736221068154274935871833124935882711284922786310458499456033", 10);
    mpz_mul(n, p, q);
    mpz_init_set_str(e, "65537", 10);
    mpz_init_set_str(d, "47300287007951581623253499459970337626349460340183668317230776568007348128414096525411753695567818713469079921983453791742764949031630073711021861365663986822750501547998528076220103101204394499863317561650316905239580025576521308918949173750232543443231132139823491162184112434957247636691500267536981561473", 10);

    const char *plaintext = "icsd aegean university crypto";

    mpz_import(plain_text, strlen(plaintext), 1, 1, 0, 0, plaintext);

    if (mpz_cmp(plain_text, n) > 0)
        abort();

    mpz_powm(chypher_text, plain_text, e, n);
    gmp_printf("Encoded:   \n%Zd\n", chypher_text);
    gmp_printf("\n");
    mpz_powm(plain_text, chypher_text, d, n);
    gmp_printf("Decoded:  \n%Zd\n", plain_text);
    gmp_printf("\n");
    char buffer[64];
    mpz_export(buffer, NULL, 1, 1, 0, 0, plain_text);
    printf("As String: \n%s\n", buffer);

    mpz_clears(p,q,plain_text, chypher_text, n, e, d, NULL);
    return 0;
}
