/*
 * Copyright 2019 Alex Beregszaszi et al.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SCOUTONE_H
#define __SCOUTONE_H

#if __cplusplus
extern "C" {
#endif

struct scoutone_input {
    const char *input;
};

struct scoutone_result {
    int result_code;
};

struct scoutone_result scoutone_run_block(struct scoutone_input);

#if __cplusplus
}
#endif

#endif
