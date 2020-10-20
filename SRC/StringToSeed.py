#!/usr/bin/python
# -*- coding: UTF-8 -*-

# Copyright (C) 2020  Aaron Feng

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# My Github homepage: https://github.com/AaronFeng753

import random
import sys

argv_list = sys.argv
seed_str = argv_list[1]
random.seed(seed_str)
print (random.randint(1, 4294967290))
