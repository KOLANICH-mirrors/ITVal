/*
 * ITVal: The IPTables Firewall Validator Copyright (C) 2004 Robert
 * Marmorstein
 * 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. A full-text
 * version is located in the LICENSE file distributed with this utility.
 * 
 * You may contact the author at rmmarm@wm.edu or by sending mail to:
 * 
 * Robert Marmorstein Department of Computer Science College of William
 * and Mary Williamsburg, VA 23185 
 */

#include <string.h>
#include "nat.h"
#include <stdlib.h>
#include <FDDL/mdd.h>
#include "firewall.h"


void BreakMASQPorts(char *str, nat_range * &NATRange, char prot, Firewall * FW){
   printf("MASQUERADE ports have not been implemented yet.\n");
   NATRange = NULL;
}

void BreakNAT(char *str, nat_range * &NATRange, char prot, Firewall * FW)
{
   char *ch;
   char word1[1024];
   char word2[1024];
   char word3[1024];
   char word4[1024];
   int length;

   address_range low;
   address_range high;

   NATRange = new nat_range;
   NATRange->next = NULL;
   NATRange->ports.port1 = 0;
   NATRange->ports.port2 = 65535;
   NATRange->ports.next = NULL;
   for (int i = 0; i < 23; i++) {
      NATRange->low[i] = 0;
      NATRange->high[i] = FW->FWForest->GetMaxVal(i);
   }

   str += 3;                    // Advance past "to:"

   length = strlen(str);
   ch = str;

   while (ch - str < length && *ch != '-' && *ch != ':') {
      word1[ch - str] = *ch;
      word2[ch - str] = *ch;    // Assume no range
      // printf("%c ", *ch);
      ch++;
   }
   word1[ch - str] = '\0';
   word2[ch - str] = '\0';
   if (*ch == '-') {            // If there IS a range, get it.
      ch++;                     // Advance past '-'
      length -= (ch - str);
      str = ch;
      while (ch - str < length && *ch != ':') {
         word2[ch - str] = *ch;
         ch++;
      }
      word2[ch - str] = '\0';
   }
   // Break Addresses into octets
   ConvertARange(word1, &low);
   ConvertARange(word2, &high);
   NATRange->addys.low = low.low;
   NATRange->addys.high = high.high;

   NATRange->low[18] = (((NATRange->addys.low / 256) / 256) / 256) % 256;
   NATRange->low[17] = ((NATRange->addys.low / 256) / 256) % 256;
   NATRange->low[16] = (NATRange->addys.low / 256) % 256;
   NATRange->low[15] = NATRange->addys.low % 256;

   NATRange->high[18] = (((NATRange->addys.high / 256) / 256) / 256) % 256;
   NATRange->high[17] = ((NATRange->addys.high / 256) / 256) % 256;
   NATRange->high[16] = (NATRange->addys.high / 256) % 256;
   NATRange->high[15] = NATRange->addys.high % 256;

   if (prot == 'a') {
      NATRange->low[14] = 0;
      NATRange->high[14] = 2;
   }
   else if (prot == 'i') {
      NATRange->low[14] = NATRange->high[14] = 0;
   }
   else if (prot == 'u') {
      NATRange->low[14] = NATRange->high[14] = 1;
   }
   else if (prot == 't') {
      NATRange->low[14] = NATRange->high[14] = 2;
   }

   if (*ch == ':') {
      ch++;                     // Advance past ':'
      length -= (ch - str);
      str = ch;
      while (ch - str < length && *ch != '-') {
         word3[ch - str] = *ch;
         word4[ch - str] = *ch; // Assume no port range
         ch++;
      }
      word3[ch - str] = '\0';
      word4[ch - str] = '\0';
      if (*ch == '-') {         // If there IS a range, get it.
         length -= (ch - str);
         str = ch;
         while (ch - str < length && *ch != ':') {
            word4[ch - str] = *ch;
            ch++;
         }
         word4[ch - str] = '\0';
      }
      sscanf(word3, "%d", &NATRange->ports.port1);
      sscanf(word4, "%d", &NATRange->ports.port2);
   }
   else {
      // No explicit port, so map to all ports.
      NATRange->ports.port1 = 0;
      NATRange->ports.port2 = 65535;
   }

   NATRange->low[13] = NATRange->low[12] = 0;
   NATRange->high[13] = NATRange->high[12] = 255;

   NATRange->low[12] = NATRange->low[12] = 0;
   NATRange->high[12] = NATRange->high[12] = 255;

   NATRange->low[11] = (NATRange->ports.port1 / 256) % 256;
   NATRange->low[10] = NATRange->ports.port1 % 256;

   NATRange->high[11] = (NATRange->ports.port2 / 256) % 256;
   NATRange->high[10] = NATRange->ports.port2 % 256;
}

void BreakNMAP(char *str, nat_range * &NATRange, Firewall * FW)
{
   char *ch;
   char word1[1024];
   int length;

   NATRange = new nat_range;
   NATRange->next = NULL;
   for (int i = 0; i < 23; i++) {
      NATRange->low[i] = 0;
      NATRange->high[i] = FW->FWForest->GetMaxVal(i);
   }

   length = strlen(str);
   ch = str;

   while (ch - str < length) {
      word1[ch - str] = *ch;
      ch++;
   }
   word1[ch - str] = '\0';
   ConvertARange(word1, &NATRange->addys);

   NATRange->low[0] = (((NATRange->addys.low / 256) / 256) / 256) % 256;
   NATRange->low[1] = ((NATRange->addys.low / 256) / 256) % 256;
   NATRange->low[2] = (NATRange->addys.low / 256) % 256;
   NATRange->low[3] = NATRange->addys.low % 256;

   NATRange->high[0] = (((NATRange->addys.high / 256) / 256) / 256) % 256;
   NATRange->high[1] = ((NATRange->addys.high / 256) / 256) % 256;
   NATRange->high[2] = (NATRange->addys.high / 256) % 256;
   NATRange->high[3] = NATRange->addys.high % 256;
}

void ProcessNATInfo(char *info, processed_nat_rule * p, Firewall * FW,
                    rule_parser * rp)
{
   char port[1024];                       // String representation of the port
   char which[1024];                      // Which protocol the port is for

   // (tcp, udp, or icmp)
   int port_val;                          // Integer representation of the port 

   port_range *newPort;                   // Temporary range to be added to the rule 

   // 
   port_range *sports;                    // List of ranges for the source ports
   port_range *dports;                    // List of ranges for the destination

   // ports

   int state;                             // States to match

   nat_range *NATRange;                   // NATted Address

   char word1[1024];                      // Key name
   char word2[1024];                      // Value 

   int flags[6];                          // Which TCP flags to match

   int length;                            // Length of the info string

   int i;

   // Initially, the port lists are empty, all states match, and the
   // no flags are considered.
   sports = NULL;
   dports = NULL;
   NATRange = NULL;

   state = 0;
   for (i = 0; i < 6; i++)
      flags[i] = (-1);

   length = strlen(info);
   while (length - 1 > 0) {
      // Consume whitespace
      while (strlen(info) - 1 > 0 && (*info == ' ' || *info == '\t')) {
         info++;
      }
      // Read the first word (the key)
      if (sscanf(info, "%1024s", word1) != EOF) {
         info += strlen(word1);
         // If it's tcp or udp, scan in a port.
         if (!strncmp(word1, "tcp", 1024) || !strncmp(word1, "udp", 1024)) {
            // Read the port number into word2
            if (sscanf(info, "%1024s", word2) != EOF) {
               info += strlen(word2);
               // Convert the string into an integer
               rp->BreakPort(word2, which, port);
               // If it's a destination port, put it in the dports
               // list.  If it's a source port, put it in the sports
               // list.
               if (!strncmp(which, "dpt", 1024)) {
                  newPort = new port_range;
                  newPort->next = dports;
                  port_val = atoi(port);
                  newPort->port1 = port_val / 256;
                  newPort->port2 = port_val % 256;
                  dports = newPort;
               }
               else if (!strncmp(which, "spt", 1024)) {
                  newPort = new port_range;
                  newPort->next = sports;
                  port_val = atoi(port);
                  newPort->port1 = port_val / 256;
                  newPort->port2 = port_val % 256;
                  sports = newPort;
               }
            }
            // If the keyword is "state", then parse the state
            // information.
         }
         else if (!strncmp(word1, "state", 1024)) {
            if (sscanf(info, "%1024s", word2) != EOF) {
               info += strlen(word2);
               rp->BreakState(word2, &state);
            }
            // If it's "flags", parse the flag information.
         }
         else if (!strncmp(word1, "flags:", 6)) {
            rp->BreakFlags(word1, flags);
         }
         else if (!strncmp(word1, "to:", 3)) {  // DNAT
            BreakNAT(word1, NATRange, p->protocol, FW);
            p->nat = NATRange;
         }
	 else if (!strncmp(word1, "masq ports:", 11)){ //MASQUERADE
            BreakMASQPorts(word1, NATRange, p->protocol, FW);
            p->nat = NATRange;
	 }
	 else if (!strncmp(word1, "redir ports", 11)){ //REDIRECT
            BreakMASQPorts(word1, NATRange, p->protocol, FW);
            p->nat = NATRange;
	 }
         else if (!strncmp(p->target, "NETMAP", 6)) {
            BreakNMAP(word1, NATRange, FW);
            p->nat = NATRange;
         }
      }
      length = strlen(info);
   }
   // Store the results in the processed_rule
   p->sports = sports;
   p->dports = dports;
   p->state = state;
   for (i = 0; i < 6; i++) {
      p->flags[i] = flags[i];
   }
}

// Convert an unprocessed rule r into a processed_rule p.
void ProcessNATRule(rule * r, processed_nat_rule * p, Firewall * FW,
                    rule_parser * rp)
{
   // Munge the source and destination addresses
   ConvertARange(r->source, p->from);
   ConvertARange(r->dest, p->to);

   // The protocol
   p->protocol = r->protocol[0];
   // The target
   strncpy(p->target, r->target, 256);

   p->nat = NULL;
   // And everything else
   ProcessNATInfo(r->info, p, FW, rp);
}
