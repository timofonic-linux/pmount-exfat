/**
 * @file conffile.h generic library for parsing of configuration files
 *
 * @author Vincent Fourmond <fourmond@debian.org>
 *         Copyright 2009,2011 by Vincent Fourmond
 * 
 * This software is distributed under the terms and conditions of the 
 * GNU General Public License. See file GPL for the full text of the license.
 */

#ifndef __conffile_h
#define __conffile_h


/**
   Some elements usable for configuration
*/

/**
   A boolean value, possibly depending on membership to groups and
   user value.
*/

typedef struct {
  /** Default value */
  int def;

  /** List of allowed groups. NULL = none*/
  gid_t * allowed_groups;

  /** List of allowed users. NULL = none*/
  uid_t * allowed_users;

  /** List of denied users. NULL = none*/
  uid_t * denied_users;
} ci_bool;

/**
   Accessors
*/
void ci_bool_set_default(ci_bool * c, int val);
int ci_bool_allowed(ci_bool * c); 
void ci_bool_dump(ci_bool * c, FILE * out);



/**
   A list of strings
*/

typedef struct {
  /**
     A NULL-terminated list of pointers to newly allocated strings, or
     NULL if there are no elements.
  */
  char ** strings;
} ci_string_list;



/**
   @todo provide macros for the initialization/declaration of the
   ci_ items?
*/

/**********************************************************************/


/**
   The type of configuration items 
*/
typedef enum {
  boolean_item,
  string_list
} ci_type;


/**
   Specification of a configuration item.
*/
typedef struct {
  /**
     The base name of the configuration item. 
     NULL for an invalid item terminating the configuration file.
  */
  const char * base;

  /**
     The type of the configuration item.
  */
  ci_type type;

  /**
     The target of the configuration item. Actual type depends on
     the item type
  */
  void * target;
} cf_spec;


/**
   Reads the given file and parse it according to the specification
   written in specs, which must be terminated by the first occurence
   of a NULL as base.
 */
int cf_read_file(FILE * file, cf_spec * specs);

#endif

